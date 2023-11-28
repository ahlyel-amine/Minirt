/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:38:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 12:15:58 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include "vector_bonus.h"
#include "draw_bonus.h"
#include "library_bonus.h"
#include "minirt_bonus.h"

void	Prime_ray(t_mrt *rt ,int x, int y, t_ray *ray,t_camera *cam)
{
	double	ndcX;
	double	ndcY;

	ray->origin = cam->cord;
	ndcX = ((double)x + 0.5) / WIDTH;
	ndcY = ((double)y + 0.5) / HEIGHT;
	ray->direction.v_x = (2 * ndcX - 1) * cam->scale * cam->aspect_ratio;
	ray->direction.v_y = (1 - 2 * ndcY) * cam->scale;
	ray->direction.v_z = 1;
	ray->direction = cam_to_world(rt->cam_matrix, &ray->direction);
	normalize(&ray->direction);
}

bool shadow_ray(t_rays *rays, t_light *light, t_objects *obj, t_hit_record *rec)
{
	t_hit_record	h_shadow;
	t_objects		*objt;

	rays->shadow_ray.origin = rec->pHit;
	rays->shadow_ray.direction = vec_sub(light->cord, rec->pHit);
	normalize(&(rays->shadow_ray.direction));
	rays->shadow_ray.origin = at(0.01, rays->shadow_ray);
	objt = get_first_close_object(&(rays->shadow_ray), obj, &h_shadow);
	return (objt && distance(rec->pHit, light->cord) > h_shadow.t);
}

t_vec	raytrace(t_data *data, t_rays *rays, t_hit_record *rec, int level)
{
	t_light_effect	light_effect;
	t_objects		*obj;
	t_rays			ref_ray;

	rays->closet_obj = get_closes_object(&(rays->ray), data->objects, rec);
	obj = rays->closet_obj;
	if (!rays->closet_obj)
		return ((t_vec){0,0,0});
	t_specular_light refl = get_specular_addr(obj);
	if (obj->type == PLANE)
		rec->h_color =  checkread_borad(rec->h_color, rec->pHit, rec);
	light_effect = get_light_effect(data, rays, obj, rec);
	level -= 1;
	if (refl.reflection > 0 &&  level > 0)
	{
		ref_ray.ray.origin = rec->pHit;
		ref_ray.ray.direction = scalar_mult(rec->nHit, 2 * dot_product(rays->ray.direction, rec->nHit));
		ref_ray.ray.direction = vec_sub(rays->ray.direction, ref_ray.ray.direction);
		normalize(&(ref_ray.ray.direction));
		light_effect.reflect = raytrace(data, &ref_ray, rec, level);
	}
	if (level <= 0)
		obj = NULL;
	t_vec color = convert_light(level, light_effect, obj, refl);
	return (color);
}