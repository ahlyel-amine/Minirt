/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersections_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:07:52 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/21 21:40:46 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "vector_bonus.h"
#include "library_bonus.h"

bool	plan_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_plane	*plan;
	t_vec	p;
	double	denom;
	double	t;

	plan = obj->object;
	denom = dot_product(plan->normalized, ray->direction);
	if (fabs(denom) > EPS)
	{
		p = vec_sub(plan->cord, ray->origin);
		t = dot_product(p, plan->normalized) / denom;
		if (t > EPS)
		{
			rec->t = t;
			rec->p_hit = at(rec->t, *ray);
			rec->n_hit = plan->normalized;
			if (dot_product(rec->n_hit, ray->direction) > 0)
				rec->n_hit = vec_nega(rec->n_hit);
			rec->h_color = create_vec((double)(plan->clr.r) / 255, \
			(double)(plan->clr.g) / 255, (double)(plan->clr.b) / 255);
			return (true);
		}
	}
	return (false);
}
