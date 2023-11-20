/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:03:01 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/20 11:16:47 by aelbrahm         ###   ########.fr       */
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
	t_vec norm = scalar_div(vec_sub(rec->pHit, sphere->cord), pow(sphere->diameter/2, 2));
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
	
	denom = dot_product(plan->normalized, ray->direction);
	if (fabs(denom) < eps)
		return (false);
	if (fabs(denom) > eps)
	{
		p = vec_sub(plan->cord, ray->origin);
		t = dot_product(p, plan->normalized) / denom;
		if (t >= eps)
		{
			rec->t = t;
			rec->pHit = at(rec->t, *ray);
			rec->nHit = plan->normalized;
			// printf("normal %f %f %f\n", rec->nHit.v_x, rec->nHit.v_y, rec->nHit.v_z);
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
bool	cylinder_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_vec	ro;
	t_cord	p;
	t_vec u;
	t_vec v;
	double	discriminant;
	double	tmp;
	double	t1;
	double	t2;
	t_cylender *cylinder = obj->object;
	u = cross_product(ray->direction, cylinder->normalized);
	v = vec_sub(ray->origin, cylinder->cord);
	v = cross_product(v, cylinder->normalized);
	p.a = dot_product(u, u);
	p.b = 2 * dot_product(u, v);
	p.c = dot_product(v, v) - pow(cylinder->diameter/2, 2);
	discriminant = p.b * p.b -  4 * p.a * p.c;
	t1 = (-p.b - sqrt(discriminant)) / (2 * p.a);
	t2 = (-p.b + sqrt(discriminant)) / (2 * p.a);
	if (discriminant <= eps || (t1 <= eps && t2 <= eps))
		return (false);
	if (t1 <= eps || (t2 > eps && (t2 < t1)))
		t1 = t2;
	rec->t = t1;
	rec->pHit = at(rec->t, *ray);
	v = vec_sub(cylinder->cord, rec->pHit);
	rec->nHit = cross_product(v, cylinder->normalized);
	rec->nHit = cross_product(rec->nHit, cylinder->normalized);
	normalize(&rec->nHit);
	// if (dot_product(rec->nHit, ray->direction))
	// 	rec->nHit = vec_nega(rec->nHit);
	rec->h_color = create_vec((double)(cylinder->clr.r) / 255, (double)(cylinder->clr.g) / 255, (double)(cylinder->clr.b) / 255);
	
	if (pow(distance(cylinder->cord, rec->pHit), 2) > (pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter/2, 2)))
		printf("out of cylinder %.1f %.1f  %.1f\n", rec->pHit.v_x, rec->pHit.v_y, rec->pHit.v_z);
	else
		printf("in of cylinder %.1f %.1f  %.1f\n", rec->pHit.v_x, rec->pHit.v_y, rec->pHit.v_z);
	
	return true;
	// p.a = dot_product(ray->direction, ray->direction) - dot_product(ray->direction, cylinder->normalized) * dot_product(ray->direction, cylinder->normalized);
	// p.b = (dot_product(ray->direction, oc) - dot_product(ray->direction, cylinder->normalized) * dot_product(oc, cylinder->normalized));
	// p.c = dot_product(oc, oc) - dot_product(oc, cylinder->normalized) * dot_product(oc, cylinder->normalized) - (cylinder->diameter / 2) * (cylinder->diameter / 2);
	// discriminant = p.b * p.b - (p.a * p.c);
	// if (discriminant < eps)
	// 	return (false);
	// if (discriminant > eps)
	// {
	// 	tmp = (-p.b - sqrt(discriminant)) / (p.a);
	// 	if (tmp <= 0.0 || tmp >= M_D)
	// 	{
	// 		tmp = (-p.b + sqrt(discriminant)) / (p.a);
	// 		if (tmp <= 0.0 || tmp >= M_D)
	// 			return (false);		
	// 	}
	// }
	// else
	// {
	// 	tmp = -p.b / p.a;
	// 	if (tmp <= 0.0 || tmp >= M_D)
	// 		return (false);
	// }
	// rec->t = tmp;
	// rec->pHit = at(rec->t, *ray);
	// rec->nHit = vec_sub(rec->pHit, cylinder->cord);
	// rec->h_color = create_vec((double)(cylinder->clr.r) / 255, (double)(cylinder->clr.g) / 255, (double)(cylinder->clr.b) / 255);
	// return (true);
}

inter_func	intersect(int type)
{
	t_objects	*obj;
	inter_func 		obj_inter[3];
	obj_inter[SPHERE] = sphere_hit;
	obj_inter[PLANE] = plan_hit;
	obj_inter[CYLENDER] = cylinder_hit;
	return (*(obj_inter + type));
}