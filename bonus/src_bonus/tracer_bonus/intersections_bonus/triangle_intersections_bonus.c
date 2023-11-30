/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersections_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:28:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/30 14:40:21 by aahlyel          ###   ########.fr       */
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

void	tri_properties(t_triangle *triangle)
{
	triangle->edge0 = vec_sub(triangle->cord2, triangle->cord1);
	triangle->edge1 = vec_sub(triangle->cord3, triangle->cord2);
	triangle->edge2 = vec_sub(triangle->cord1, triangle->cord3);
	triangle->normalizer = cross_product(triangle->edge0, triangle->edge1);
	// normalize(&triangle->normalizer);
}

bool	check_tri_inter(t_hit_record *rec, t_triangle *tri)
{
	t_vec c1, c2, c3;
	c1 = vec_sub(rec->pHit, tri->cord1);
	c2 = vec_sub(rec->pHit, tri->cord2);
	c3 = vec_sub(rec->pHit, tri->cord3);
	if (dot_product(cross_product(tri->edge0, c1), tri->normalizer) > 0 &&
		dot_product(cross_product(tri->edge1, c2), tri->normalizer) > 0 &&
		dot_product(cross_product(tri->edge2, c3), tri->normalizer) > 0)
	{
		// rec->nHit = normalized(tri->normalizer);
		rec->h_color = create_vec((double)(tri->clr.r) / 255, (double)(tri->clr.g) / 255, (double)(tri->clr.b) / 255);
		return (true);
	}	
	return (false);
		
}
bool	triangle_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_triangle	*triangle;
	double		dis;
	double 		dinom;

	triangle = (t_triangle *)obj->object;
	tri_properties(triangle);
	dinom = dot_product(ray->direction, triangle->normalizer);
	if (fabs(dinom) < eps)
		return (false);
	dis = -dot_product(triangle->normalizer, triangle->cord1);
	rec->t = -(dot_product(ray->origin, triangle->normalizer) + dis) / dinom;
	if (rec->t < eps)
		return (false);
	rec->pHit = at(rec->t, *ray);
	if (check_tri_inter(rec, triangle))
	{
		if (dot_product(rec->nHit, ray->direction) > eps)
			rec->nHit = vec_nega(rec->nHit);
		return (true);
	}
	return (false);
	// return (check_tri_inter(rec, triangle));
}