/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:07:48 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 11:47:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "vector_bonus.h"
#include "library_bonus.h"
#include "tracer_bonus.h"
#include "libft.h"
#include <stdlib.h>

static void	calculate_disk_plan(t_cylender *cylinder, t_objects *obj, bool is_top)
{
	t_plane *plan;

	plan = obj->object;
	plan->normalized = cylinder->normalized;
	if (is_top)
		plan->cord = vec_addition(cylinder->cord, scalar_mult(cylinder->normalized, cylinder->height * 0.5));
	else
		plan->cord = vec_sub(cylinder->cord, scalar_mult(cylinder->normalized, cylinder->height * 0.5));
}

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
	t_objects		*plan;

	rec->t = M_D;
	plan = malloc(sizeof(t_objects));
	plan->next = NULL;
	plan->object = malloc(sizeof(t_plane));
	ft_memset(plan->object, 0, sizeof(t_plane));
	cylinder = obj->object;
	calculate_disk_plan(cylinder, plan,true);
	((t_plane *)(plan->object))->clr = cylinder->clr;
	calculate_disk_plan(cylinder, plan, false);
	if (plan_hit(ray, plan, &tmp_rec)
		&& distance(tmp_rec.pHit, ((t_plane *)(plan->object))->cord) \
		<= ((cylinder->diameter * 0.5) - 0.002)
		&& rec->t > tmp_rec.t)
		*rec = tmp_rec;
	if (cylinder_hit(ray, cylinder, &tmp_rec)
		&& pow(distance(cylinder->cord, tmp_rec.pHit), 2) \
		<= pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2))
		*rec = tmp_rec;
	return (rec->t < M_D && rec->t > eps);
}
