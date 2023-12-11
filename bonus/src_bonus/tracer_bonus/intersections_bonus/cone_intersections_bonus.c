/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersections_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:50:06 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/11 15:09:51 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs_bonus.h"
#include "vector_bonus.h"
#include "tools_bonus.h"
#include "library_bonus.h"

// struct s_cone
// {
//     t_vec apex;
//     t_vec axis;
//     t_vec point;
//     double half_angle;
// }   t_cone;

bool	cone_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
    t_cone *cone;
    
    cone = (t_cone *)obj->object;
    double cosTheta2 = cos(cone->half_angle) * cos(cone->half_angle);
    double sinTheta2 = 1.0 - cosTheta2;

    t_vec cone_origin = vec_sub(ray->origin, cone->cord);
    // ray->direction = cross_product(ray->direction, cone->axis);
    // double a = cosTheta2 * pow(ray->direction.v_x, 2) + cosTheta2 * pow(ray->direction.v_z, 2) - sinTheta2 * pow(ray->direction.v_y, 2);
    double a = pow(dot_product(ray->direction, cone->normalized), 2) - cosTheta2;
    // double b = 2 * (cosTheta2 * ray->direction.v_x * cone_origin.v_x + cosTheta2 * ray->direction.v_z * cone_origin.v_z - sinTheta2 * ray->direction.v_y * cone_origin.v_y);
    double b = 2 * ((dot_product(ray->direction, cone->normalized) * dot_product(cone_origin, cone->normalized)) - dot_product(ray->direction, cone_origin) * cosTheta2);
    // double c = cosTheta2 * pow(cone_origin.v_x, 2) + cosTheta2 * pow(cone_origin.v_z, 2) - sinTheta2 * pow(cone_origin.v_y, 2);
    double c = pow(dot_product(cone_origin, cone->normalized), 2) - cosTheta2 * dot_product(cone_origin, cone_origin);
    double discriminant = b * b - 4 * a * c;
    if (discriminant < eps)
        return (false);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    double t2 = (-b - sqrt(discriminant)) / (2 * a);
    double t = MIN(t1, t2);
    if (t < 0) 
        return (false);
    rec->t = t;
	rec->pHit = at(rec->t, *ray);
    if (dot_product(vec_sub(rec->pHit, cone->cord), cone->normalized) > eps)
        return (false);
    if (distance(cone->cord, rec->pHit) > cone->height)
        return (false);
	t_vec norm = vec_sub(rec->pHit, cone->cord);
    rec->nHit = normalized(cross_product(cross_product(norm, cone->normalized), cone->normalized));
    if (dot_product(rec->nHit, ray->direction) > 0)
		rec->nHit = vec_nega(rec->nHit);
	rec->h_color = create_vec((double)(cone->clr.r) / 255, (double)(cone->clr.g) / 255, (double)(cone->clr.b) / 255);
	return (true);
}
