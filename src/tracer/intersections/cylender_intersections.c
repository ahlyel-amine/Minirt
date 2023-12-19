/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:07:48 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/17 11:20:21 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vector.h"
#include "library.h"
#include "tracer.h"
#include "libft.h"
#include <stdlib.h>

static bool	solve_quad(t_ray *ray, t_cylender *cylinder, t_hit_record *rec)
{
	t_vec	orthg;
	t_vec	v;
	t_cord	p;
	t_cord	param;

	orthg = cross_product(ray->direction, cylinder->normalized);
	v = cross_product(vec_sub(ray->origin, cylinder->cord), \
	cylinder->normalized);
	p.a = dot_product(orthg, orthg);
	p.b = 2 * dot_product(orthg, v);
	p.c = dot_product(v, v) - pow(cylinder->diameter * 0.5, 2);
	param.a = p.b * p.b - 4 * p.a * p.c;
	param.b = (-p.b - sqrt(param.a)) / (2 * p.a);
	param.c = (-p.b + sqrt(param.a)) / (2 * p.a);
	if (param.a <= EPS || (param.b <= EPS && param.c <= EPS))
		return (false);
	if (param.b <= EPS || (param.c > EPS && (param.c < param.b)))
		param.b = param.c;
	return (rec->t = param.b, true);
}

static bool	cylinder_hit(t_ray *ray, t_cylender *cylinder, t_hit_record *rec)
{
	t_cord	p;
	t_vec	v;

	if (!solve_quad(ray, cylinder, rec))
		return (false);
	rec->p_hit = at(rec->t, *ray);
	v = vec_sub(rec->p_hit, cylinder->cord);
	rec->n_hit = normalized(cross_product(cross_product(v, \
	cylinder->normalized), cylinder->normalized));
	if (dot_product(rec->n_hit, ray->direction) > 0)
		rec->n_hit = vec_nega(rec->n_hit);
	if (pow(distance(cylinder->cord, rec->p_hit), 2) > \
	(pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2)))
		return (false);
	rec->h_color = create_vec((double)(cylinder->clr.r) / 255, \
	(double)(cylinder->clr.g) / 255, (double)(cylinder->clr.b) / 255);
	return (true);
}

bool	f_cylinder_render(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_hit_record	tmp_rec;
	t_cylender		*cylinder;
	t_plane			*plan;

	rec->t = M_D;
	cylinder = obj->object;
	plan = cylinder->p_face->object;
	plan->clr = cylinder->clr;
	if (intersect(PLANE)(ray, cylinder->p_face, &tmp_rec)
		&& distance(tmp_rec.p_hit, plan->cord) \
		<= ((cylinder->diameter * 0.5))
		&& rec->t > tmp_rec.t)
		*rec = tmp_rec;
	plan = cylinder->p_face->next->object;
	plan->clr = cylinder->clr;
	if (intersect(PLANE)(ray, cylinder->p_face->next, &tmp_rec)
		&& distance(tmp_rec.p_hit, plan->cord) \
		<= ((cylinder->diameter * 0.5))
		&& rec->t > tmp_rec.t)
		*rec = tmp_rec;
	if (cylinder_hit(ray, cylinder, &tmp_rec)
		&& pow(distance(cylinder->cord, tmp_rec.p_hit), 2) \
		<= pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2))
		*rec = tmp_rec;
	return (rec->t < M_D && rec->t > EPS);
}
