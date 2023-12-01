/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender_intersections_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:07:48 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/01 19:30:14 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "vector_bonus.h"
#include "library_bonus.h"
#include "tracer_bonus.h"
#include "libft.h"
#include <stdlib.h>


static bool	solve_quad(t_ray *ray, t_cylender *cylinder, t_hit_record *rec)
{
	t_vec   orthg;
	t_vec   v;
	t_cord  p;
	t_cord  param;

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

static bool	cylinder_hit(t_ray *ray, t_cylender *cylinder, t_hit_record *rec)
{
	t_cord		p;
	t_vec		v;

	if (!solve_quad(ray, cylinder, rec))
		return (false);
	rec->pHit = at(rec->t, *ray);
	v = vec_sub(rec->pHit, cylinder->cord);
	rec->nHit = normalized(cross_product(cross_product(v, cylinder->normalized), cylinder->normalized));
	if (dot_product(rec->nHit, ray->direction) > 0)
		rec->nHit = vec_nega(rec->nHit);
	if (pow(distance(cylinder->cord, rec->pHit), 2) > (pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2)))
		return (false);
	rec->h_color = create_vec((double)(cylinder->clr.r) / 255, (double)(cylinder->clr.g) / 255, (double)(cylinder->clr.b) / 255);
	return (true);
}

bool	f_cylinder_render(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_hit_record	tmp_rec;
	t_cylender	*cylinder;
	t_plane		*plan;

	rec->t = M_D;
	cylinder = obj->object;
	plan = cylinder->p_face->object;
	plan->clr = cylinder->clr;
	if (intersect(PLANE)(ray, cylinder->p_face, &tmp_rec)
		&& distance(tmp_rec.pHit, plan->cord) \
		<= ((cylinder->diameter * 0.5))
		&& rec->t > tmp_rec.t)
		*rec = tmp_rec;
	plan = cylinder->p_face->next->object;
	plan->clr = cylinder->clr;
	if (intersect(PLANE)(ray, cylinder->p_face->next, &tmp_rec)
		&& distance(tmp_rec.pHit, plan->cord) \
		<= ((cylinder->diameter * 0.5))
		&& rec->t > tmp_rec.t)
		*rec = tmp_rec;
	if (cylinder_hit(ray, cylinder, &tmp_rec)
		&& pow(distance(cylinder->cord, tmp_rec.pHit), 2) \
		<= pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2))
		*rec = tmp_rec;
	return (rec->t < M_D && rec->t > eps);
}
