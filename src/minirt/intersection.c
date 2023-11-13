/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:03:01 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/13 05:23:15 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"
#include "library.h"
#include "vector.h"

void	Prime_ray(t_mrt *rt ,int x, int y, t_ray *ray,t_camera *cam)
{
	double	ndcX;
	double	ndcY;
	double	aspect_ratio;

	aspect_ratio = WIDTH / (double)HEIGHT;
	ray->origin = cam->cord;
	ndcX = ((double)x + 0.5) / WIDTH;
	ndcY = ((double)y + 0.5) / HEIGHT;
	ray->direction.v_x = (2 * ndcX - 1) * tan(((double)(cam->v_field) / 2) * M_PI / 180) * aspect_ratio;
	ray->direction.v_y = (2 * ndcY - 1) * tan(((double)(cam->v_field) / 2) * M_PI / 180);
	ray->direction.v_z = 0.5;
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
	discriminant = p.b * p.b - (p.a * p.c);
	if (discriminant < eps)
		return (false);
	if (discriminant > eps)
	{
		tmp = (-p.b - sqrt(discriminant)) / (p.a);
		if (tmp <= 0.0 || tmp >= M_D)
		{
			tmp = (-p.b + sqrt(discriminant)) / (p.a);
			if (tmp <= 0.0 || tmp >= M_D)
				return (false);		
		}
	}else
	{
		tmp = -p.b / p.a;
		if (tmp <= 0.0 || tmp >= M_D)
			return (false);
	}
	rec->t = tmp;
	rec->pHit = at(rec->t, *ray);
	rec->nHit = normalized(vec_sub(rec->pHit, sphere->cord));
	
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
	if (fabs(denom) > eps)
	{
		p = vec_sub(plan->cord, ray->origin);
		t = dot_product(p, plan->normalized) / denom;
		if (t > eps)
		{
			rec->t = t;
			rec->pHit = at(rec->t, *ray);
			rec->nHit = plan->normalized;
			if (dot_product(rec->nHit, ray->direction) > 0)
				rec->nHit = vec_nega(rec->nHit);
			rec->h_color = create_vec((double)(plan->clr.r) / 255, (double)(plan->clr.g) / 255, (double)(plan->clr.b) / 255);
			return (true);
		}
	}
	return (false);
}

bool	cylinder_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_vec	oc;
	t_cord	p;
	double	discriminant;
	double	tmp;
	t_cylender *cylinder = obj->object;
	oc = vec_sub(ray->origin, cylinder->cord);
	p.a = dot_product(ray->direction, ray->direction) - dot_product(ray->direction, cylinder->normalized) * dot_product(ray->direction, cylinder->normalized);
	p.b = 2 * (dot_product(ray->direction, oc) - dot_product(ray->direction, cylinder->normalized) * dot_product(oc, cylinder->normalized));
	p.c = dot_product(oc, oc) - dot_product(oc, cylinder->normalized) * dot_product(oc, cylinder->normalized) - (cylinder->diameter / 2) * (cylinder->diameter / 2);
	discriminant = p.b * p.b - (p.a * p.c);
	if (discriminant < eps)
		return (false);
	if (discriminant > eps)
	{
		tmp = (-p.b - sqrt(discriminant)) / (p.a);
		if (tmp <= 0.0 || tmp >= M_D)
		{
			tmp = (-p.b + sqrt(discriminant)) / (p.a);
			if (tmp <= 0.0 || tmp >= M_D)
				return (false);		
		}
	}
	else
	{
		tmp = -p.b / p.a;
		if (tmp <= 0.0 || tmp >= M_D)
			return (false);
	}
	rec->t = tmp;
	rec->pHit = at(rec->t, *ray);
	rec->nHit = vec_sub(rec->pHit, cylinder->cord);
	rec->h_color = create_vec((double)(cylinder->clr.r) / 255, (double)(cylinder->clr.g) / 255, (double)(cylinder->clr.b) / 255);
	return (true);
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