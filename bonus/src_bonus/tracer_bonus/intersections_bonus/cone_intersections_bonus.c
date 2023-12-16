/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersections_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:50:06 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/16 16:17:07 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_bonus.h"
#include "vector_bonus.h"
#include "tools_bonus.h"
#include "library_bonus.h"

bool	cone_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
    t_cone  *cone;
    t_vec   cone_origin;
    t_vec   norm;
    double  discriminant;
    double  cosTheta2;
    double  t2;
    double  t1;
    double  t;
    double  a;
    double  b;
    double  c;

    cone = (t_cone *)obj->object;
    cosTheta2 = cos(cone->half_angle) * cos(cone->half_angle);
    cone_origin = vec_sub(ray->origin, cone->cord);
    a = pow(dot_product(ray->direction, cone->normalized), 2) - cosTheta2;
    b = 2 * ((dot_product(ray->direction, cone->normalized) * dot_product(cone_origin, cone->normalized)) - dot_product(ray->direction, cone_origin) * cosTheta2);
    c = pow(dot_product(cone_origin, cone->normalized), 2) - cosTheta2 * dot_product(cone_origin, cone_origin);
    discriminant = b * b - 4 * a * c;
    if (discriminant < eps)
        return (false);
    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);
    t = min(t1, t2);
    if (t < 0) 
        return (false);
    rec->t = t;
	rec->p_hit = at(rec->t, *ray);
    if (dot_product(vec_sub(rec->p_hit, cone->cord), cone->normalized) > eps)
        return (false);
    if (distance(cone->cord, rec->p_hit) > cone->height)
        return (false);
	norm = vec_sub(rec->p_hit, cone->cord);
    rec->n_hit = normalized(cross_product(cross_product(norm, cone->normalized), cone->normalized));
    if (dot_product(rec->n_hit, ray->direction) > 0)
		rec->n_hit = vec_nega(rec->n_hit);
	rec->h_color = create_vec((double)(cone->clr.r) / 255, (double)(cone->clr.g) / 255, (double)(cone->clr.b) / 255);
	return (true);
}
