/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:03:01 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/21 14:29:55 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"
#include "library.h"
#include "vector.h"
#include "../../libft/include/libft.h"

void	Prime_ray(t_mrt *rt ,int x, int y, t_ray *ray,t_camera *cam)
{
	double	ndcX;
	double	ndcY;

	ray->origin = cam->cord;
	ndcX = ((double)x + 0.5) / WIDTH;
	ndcY = ((double)y + 0.5) / HEIGHT;
	ray->direction.v_x = (2 * ndcX - 1) * cam->scale * cam->aspect_ratio;
	ray->direction.v_y = (1 - 2 * ndcY) * cam->scale;
	ray->direction.v_z = 1;
	ray->direction = cam_to_world(rt->cam_matrix, &ray->direction);
	normalize(&ray->direction);
}

bool	sphere_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_vec	oc;
	t_cord	p;
	double	discriminant;
	double	tmp;
	t_sphere *sphere = obj->object;
	oc = vec_sub(ray->origin, sphere->cord);
	p.a = dot_product(ray->direction, ray->direction);
	p.b = dot_product(oc, ray->direction);

	p.c = dot_product(oc, oc) - pow(sphere->diameter/2, 2);
	discriminant = p.b * p.b -   p.a * p.c;
	if (discriminant < eps)
		return (false);
	if (discriminant > eps)
	{
		tmp = (-p.b - sqrt(discriminant)) / (p.a);
		if (tmp <= eps || tmp >= M_D)
		{
			tmp = (-p.b + sqrt(discriminant)) / (p.a);
			if (tmp <= eps || tmp >= M_D)
				return (false);		
		}
	}else
	{
		tmp = -p.b / p.a;
		if (tmp <= eps || tmp >= M_D)
			return (false);
	}
	rec->t = tmp;
	rec->pHit = at(rec->t, *ray);
	t_vec norm = scalar_div(vec_sub(rec->pHit, sphere->cord), pow(sphere->diameter * 0.5, 2));
	// if (dot_product(norm, norm) == 0.0)
	// 	return (false);
	rec->nHit = normalize(&norm);
	if (dot_product(rec->nHit, ray->direction) > 0.0)
		rec->nHit = vec_nega(rec->nHit);
	// printf("sphere clooor %d %d %d\n", sphere->clr.r, sphere->clr.g, sphere->clr.b);
	rec->h_color = create_vec((double)(sphere->clr.r) / 255, (double)(sphere->clr.g) / 255, (double)(sphere->clr.b) / 255);
	return (true);
}

bool	plan_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	double	denom;
	double	t;
	t_vec	p;
	t_plane *plan = obj->object;
	// normalize(&plan->normalized);
	denom = dot_product(plan->normalized, ray->direction);
	if (fabs(denom) < eps)
		return (false);
	if (fabs(denom) >= eps)
	{
		p = vec_sub(plan->cord, ray->origin);
		t = dot_product(p, plan->normalized) / denom;
		if (t > eps)
		{
			rec->t = t;
			rec->pHit = at(rec->t, *ray);
			rec->nHit = plan->normalized;
			if (dot_product(rec->nHit, ray->direction) > 0.0)
				rec->nHit = vec_nega(rec->nHit);
			rec->h_color = create_vec((double)(plan->clr.r) / 255, (double)(plan->clr.g) / 255, (double)(plan->clr.b) / 255);
			return (true);
		}
	}
	return (false);
}
int isZero(double value, double epsilon) {
    return fabs(value) < epsilon;
}

bool	solve_quad(t_ray *ray, t_cylender *cylinder, t_hit_record *rec)
{
	t_vec orthg;
	t_vec v;
	t_cord p;
	t_cord param;

	//pram.a => discriminant, param.b => solution 1, param.c => solution 2
	orthg = cross_product(ray->direction, cylinder->normalized);
	v = cross_product(vec_sub(ray->origin, cylinder->cord), cylinder->normalized);
	p.a = dot_product(orthg, orthg);
	p.b = 2 * dot_product(orthg, v);
	p.c = dot_product(v, v) - pow(cylinder->diameter * 0.5, 2);
	param.a = p.b * p.b -  4 * p.a * p.c;
	param.b = (-p.b - sqrt(param.a)) / (2 * p.a);
	param.c = (-p.b + sqrt(param.a)) / (2 * p.a);
	if (param.a <= eps || (param.b <= eps && param.c <= eps))
		return (false);
	if (param.b <= eps || (param.c > eps && (param.c < param.b)))
		param.b = param.c;
	return (rec->t = param.b, true);
	
}
void calculate_disk_plan(t_cylender *cylinder, t_objects *obj, bool	is_top)
{
	t_plane	*plan;
	plan = obj->object;

	plan->normalized = cylinder->normalized;
	if (is_top)
		plan->cord = vec_addition(cylinder->cord, scalar_mult(cylinder->normalized, cylinder->height * 0.5));
	else
		plan->cord = vec_sub(cylinder->cord, scalar_mult(cylinder->normalized, cylinder->height * 0.5));
}

static bool	cylinder_hit(t_ray *ray, t_cylender *cylinder, t_hit_record *rec)
{
	// t_cylender	*cylinder;
	t_cord		p;
	t_vec		v;

	// cylinder = obj->object;
	if (!solve_quad(ray, cylinder, rec))
		return false;
	rec->pHit = at(rec->t, *ray);
	v = vec_sub(rec->pHit, cylinder->cord);
	rec->nHit = normalized(cross_product(cross_product(v, cylinder->normalized), cylinder->normalized));
	if (dot_product(rec->nHit, ray->direction))
		rec->nHit = vec_nega(rec->nHit);
	if (pow(distance(cylinder->cord, rec->pHit), 2) > (pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2)))
		return false;
	rec->h_color = create_vec((double)(cylinder->clr.r) / 255, (double)(cylinder->clr.g) / 255, (double)(cylinder->clr.b) / 255);
	return true;
}

bool	f_cylinder_render(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_cylender	*cylinder;
	t_objects		*plan;
	rec->t = M_D;
	plan = malloc(sizeof(t_objects));
	plan->next = NULL;
	plan->object = malloc(sizeof(t_plane));
	ft_memset(plan->object, 0, sizeof(t_plane));
	t_hit_record	tmp_rec;
	cylinder = obj->object;
	calculate_disk_plan(cylinder, plan,true);
	((t_plane *)(plan->object))->clr = cylinder->clr;
	// printf("plan type %f %f %f\n", ((t_plane *)(plan->object))->cord.v_x, ((t_plane *)(plan->object))->cord.v_y, ((t_plane *)(plan->object))->cord.v_z);
	// printf("obj->type %d\n", plan.type);
		
	calculate_disk_plan(cylinder, plan, false);
	// printf("plan2 type %f %f %f\n", ((t_plane *)(plan->object))->cord.v_x, ((t_plane *)(plan->object))->cord.v_y, ((t_plane *)(plan->object))->cord.v_z);

	// if (plan_hit(ray, plan, &tmp_rec)
	// 	&& distance(tmp_rec.pHit, ((t_plane *)(plan->object))->cord) <= ((cylinder->diameter * 0.5) - 0.002)
	// 	&& rec->t > tmp_rec.t)
	// {
	// 	*rec = tmp_rec;
	// 	puts("here");
	// }	
	if (cylinder_hit(ray, cylinder, &tmp_rec)
		&& pow(distance(cylinder->cord, tmp_rec.pHit), 2) <= pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2))
		*rec = tmp_rec;
	return (rec->t < M_D && rec->t > eps);
}

inter_func	intersect(int type)
{
	t_objects	*obj;
	inter_func 		obj_inter[3];
	obj_inter[SPHERE] = sphere_hit;
	obj_inter[PLANE] = plan_hit;
	obj_inter[CYLENDER] = f_cylinder_render;
	return (*(obj_inter + type));
}