/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersections_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:50:06 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/17 22:04:36 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_bonus.h"
#include "vector_bonus.h"
#include "tools_bonus.h"
#include "library_bonus.h"

double	cone_quadratic_calculs(t_ray *ray, t_objects *obj, bool *success)
{
	t_cone	*cone;
	t_vec	cone_origin;
	double	discriminant;
	double	cos_theta2;
	t_cord	quad;

	cone = (t_cone *)obj->object;
	cos_theta2 = cos(cone->half_angle) * cos(cone->half_angle);
	cone_origin = vec_sub(ray->origin, cone->cord);
	quad.a = pow(dot_product(ray->direction, cone->normalized), 2) - cos_theta2;
	quad.b = 2 * ((dot_product(ray->direction, cone->normalized) * \
	dot_product(cone_origin, cone->normalized)) - \
	dot_product(ray->direction, cone_origin) * cos_theta2);
	quad.c = pow(dot_product(cone_origin, cone->normalized), 2) - cos_theta2 * \
	dot_product(cone_origin, cone_origin);
	discriminant = quad.b * quad.b - 4 * quad.a * quad.c;
	if (discriminant <EPS)
		return (*success = false, 0);
	quad.c = (-quad.b + sqrt(discriminant)) / (2 * quad.a);
	quad.b = (-quad.b - sqrt(discriminant)) / (2 * quad.a);
	discriminant = min(quad.b, quad.c);
	if (discriminant < 0)
		return (*success = false, 0);
	return (discriminant);
}

bool	cone_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_cone	*cone;
	t_vec	norm;
	bool	success;
	double	t;

	cone = (t_cone *)obj->object;
	success = true;
	t = cone_quadratic_calculs(ray, obj, &success);
	if (!success)
		return (false);
	rec->t = t;
	rec->p_hit = at(rec->t, *ray);
	if (dot_product(vec_sub(rec->p_hit, cone->cord), cone->normalized) >EPS)
		return (false);
	if (distance(cone->cord, rec->p_hit) > cone->height)
		return (false);
	norm = vec_sub(rec->p_hit, cone->cord);
	rec->n_hit = normalized(cross_product(\
	cross_product(norm, cone->normalized), cone->normalized));
	if (dot_product(rec->n_hit, ray->direction) > 0)
		rec->n_hit = vec_nega(rec->n_hit);
	rec->h_color = create_vec((double)(cone->clr.r) / 255, \
	(double)(cone->clr.g) / 255, (double)(cone->clr.b) / 255);
	return (true);
}
