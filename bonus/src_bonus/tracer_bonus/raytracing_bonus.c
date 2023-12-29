/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:38:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/29 12:25:53 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include "vector_bonus.h"
#include "draw_bonus.h"
#include "library_bonus.h"
#include "minirt_bonus.h"

void	prime_ray(int x, int y, t_ray *ray, t_camera *cam)
{
	double	ndc_x;
	double	ndc_y;

	ray->origin = cam->cord;
	ndc_x = ((double)x + 0.5) / WIDTH;
	ndc_y = ((double)y + 0.5) / HEIGHT;
	ray->direction.v_x = (2 * ndc_x - 1) * cam->scale * cam->aspect_ratio;
	ray->direction.v_y = (1 - 2 * ndc_y) * cam->scale;
	ray->direction.v_z = 1;
	ray->direction = cam_to_world(cam->tr_matrix, &ray->direction);
	normalize(&ray->direction);
}

bool	shadow_ray(t_rays *rays, t_light *light, \
t_objects *obj, t_hit_record *rec)
{
	t_hit_record	h_shadow;
	t_objects		*objt;

	rays->shadow_ray.origin = rec->p_hit;
	rays->shadow_ray.direction = vec_sub(light->cord, rec->p_hit);
	normalize(&(rays->shadow_ray.direction));
	rays->shadow_ray.origin = at(0.01, rays->shadow_ray);
	objt = get_closes_object(&(rays->shadow_ray), obj, &h_shadow);
	return (objt && distance(rec->p_hit, light->cord) > h_shadow.t);
}

t_vec	raytrace(t_data *data, t_rays *rays, t_hit_record *rec, int level)
{
	t_light_effect	light_effect;
	t_features		refl;
	t_rays			ref_ray;

	rays->closet_obj = get_closes_object(&(rays->ray), data->objects, rec);
	if (!rays->closet_obj)
		return ((t_vec){0, 0, 0});
	refl = get_specular_addr(rays->closet_obj);
	if (rays->closet_obj->features.bump)
		handle_bump(rec, rays->closet_obj);
	if (rays->closet_obj->features.checkred)
		checkread_borad(rays->closet_obj, rec);
	light_effect = get_light_effect(data, rays, rays->closet_obj, rec);
	if (--level > 0 && refl.reflection > 0)
	{
		ref_ray.ray.origin = rec->p_hit;
		ref_ray.ray.direction = scalar_mult(rec->n_hit, 2 * \
		dot_product(rays->ray.direction, rec->n_hit));
		ref_ray.ray.direction = vec_sub(rays->ray.direction, \
		ref_ray.ray.direction);
		normalize(&(ref_ray.ray.direction));
		light_effect.reflect = raytrace(data, &ref_ray, rec, level);
	}
	return (convert_light(level, light_effect, refl));
}
