/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:07:54 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/18 17:34:56 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vector.h"
#include "library.h"

double	sphere_quad(t_cord *p, t_objects *shape, t_ray *ray)
{
	t_vec		oc;
	t_sphere	*sphere;
	double		discriminant;

	sphere = shape->object;
	oc = vec_sub(ray->origin, sphere->cord);
	p->a = dot_product(ray->direction, ray->direction);
	p->b = dot_product(oc, ray->direction);
	p->c = dot_product(oc, oc) - pow(sphere->diameter * 0.5, 2);
	return (discriminant = p->b * p->b - (p->a * p->c));
}

void	update_record(t_hit_record *rec, t_sphere *s, t_ray *r, double distance)
{
	rec->t = distance;
	rec->p_hit = at(distance, *r);
	rec->n_hit = vec_sub(rec->p_hit, s->cord);
	normalize(&rec->n_hit);
	rec->h_color = create_vec((double)(s->clr.r) / 255, \
	(double)(s->clr.g) / 255, (double)(s->clr.b) / 255);
}

bool	sphere_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	double	discriminant;
	double	tmp;
	t_cord	p;

	discriminant = sphere_quad(&p, obj, ray);
	if (discriminant <EPS)
		return (false);
	if (discriminant >EPS)
	{
		tmp = (-p.b - sqrt(discriminant)) / (p.a);
		if (tmp <=EPS || tmp >= M_D)
		{
			tmp = (-p.b + sqrt(discriminant)) / (p.a);
			if (tmp <=EPS || tmp >= M_D)
				return (false);
		}
	}
	else
	{
		tmp = -p.b / p.a;
		if (tmp <=EPS || tmp >= M_D)
			return (false);
	}
	update_record(rec, (t_sphere *)(obj->object), ray, tmp);
	return (true);
}
