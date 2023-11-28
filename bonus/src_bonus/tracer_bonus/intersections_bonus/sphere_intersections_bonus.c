/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:07:54 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 11:47:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "vector_bonus.h"
#include "library_bonus.h"

bool	sphere_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_vec       oc;
	t_cord      p;
	double      discriminant;
	double      tmp;
	t_sphere    *sphere;

    sphere = obj->object;
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
		if (tmp <= eps || tmp >= M_D)
		{
			tmp = (-p.b + sqrt(discriminant)) / (p.a);
			if (tmp <= eps || tmp >= M_D)
				return (false);		
		}
	}
	else
	{
		tmp = -p.b / p.a;
		if (tmp <= eps || tmp >= M_D)
			return (false);
	}
	rec->t = tmp;
	rec->pHit = at(rec->t, *ray);
	t_vec norm = vec_sub(rec->pHit, sphere->cord);
	rec->nHit = normalize(&norm);
	rec->h_color = create_vec((double)(sphere->clr.r) / 255, (double)(sphere->clr.g) / 255, (double)(sphere->clr.b) / 255);
	return (true);
}
