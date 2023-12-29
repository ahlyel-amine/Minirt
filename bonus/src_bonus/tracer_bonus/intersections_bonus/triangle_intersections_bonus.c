/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersections_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:28:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/29 13:36:23 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "vector_bonus.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool	check_tri_inter(t_hit_record *rec, t_triangle *tri)
{
	t_vec	c1;
	t_vec	c2;
	t_vec	c3;

	c1 = vec_sub(rec->p_hit, tri->cord1);
	c2 = vec_sub(rec->p_hit, tri->cord2);
	c3 = vec_sub(rec->p_hit, tri->cord3);
	if (dot_product(cross_product(tri->edge0, c1), tri->normalizer) > 0 \
	&& dot_product(cross_product(tri->edge1, c2), tri->normalizer) > 0 \
	&& dot_product(cross_product(tri->edge2, c3), tri->normalizer) > 0)
	{
		rec->h_color = create_vec((double)(tri->clr.r) / 255, \
		(double)(tri->clr.g) / 255, (double)(tri->clr.b) / 255);
		return (true);
	}
	return (false);
}

bool	triangle_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_triangle	*triangle;
	double		dis;
	double		dinom;

	triangle = (t_triangle *)obj->object;
	dinom = dot_product(ray->direction, triangle->normalizer);
	if (fabs(dinom) < EPS)
		return (false);
	dis = -dot_product(triangle->normalizer, triangle->cord1);
	rec->t = -(dot_product(ray->origin, triangle->normalizer) + dis) / dinom;
	if (rec->t < EPS)
		return (false);
	rec->p_hit = at(rec->t, *ray);
	if (check_tri_inter(rec, triangle))
	{
		rec->n_hit = triangle->normalizer;
		if (dot_product(rec->n_hit, ray->direction) > EPS)
			rec->n_hit = vec_nega(rec->n_hit);
		return (true);
	}
	return (false);
}
