/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:38:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/04 23:09:38 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tracer.h"
#include "structs.h"
#include "tools.h"
#include "vector.h"
#include "library.h"
#include "minirt.h"


void	Prime_ray(int x, int y, t_ray *ray,t_camera *cam)
{
	double	ndcX;
	double	ndcY;

	ray->origin = cam->cord;
	ndcX = ((double)x + 0.5) / WIDTH;
	ndcY = ((double)y + 0.5) / HEIGHT;
	ray->direction.v_x = (2 * ndcX - 1) * cam->scale * cam->aspect_ratio;
	ray->direction.v_y = (1 - 2 * ndcY) * cam->scale;
	ray->direction.v_z = 1;
	ray->direction = cam_to_world(cam->tr_matrix, &ray->direction);
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
	objt = get_closes_object(&(rays->shadow_ray), obj, &h_shadow);
	
	return (objt && distance(rec->pHit, light->cord) > h_shadow.t);
}

t_vec	raytrace(t_data *data, t_rays *rays, t_hit_record *rec)
{
	t_light_effect	light_effect;
	t_objects		*obj;
	t_rays			ref_ray;

	rays->closet_obj = get_closes_object(&(rays->ray), data->objects, rec);
	obj = rays->closet_obj;
	if (!rays->closet_obj)
		return ((t_vec){0,0,0});
	rec->nHit = (t_vec){rec->nHit.v_x + 0.9, rec->nHit.v_y + 0.9, rec->nHit.v_z + 0.9};
	normalize(&rec->nHit);
	if (obj->type == SPHERE)
		printf("nHit: %f %f %f\n", rec->nHit.v_x, rec->nHit.v_y, rec->nHit.v_z);
	light_effect = get_light_effect(data, rays, obj, rec);
	ref_ray.ray.origin = rec->pHit;
	ref_ray.ray.direction = scalar_mult(rec->nHit, 2 * dot_product(rays->ray.direction, rec->nHit));
	ref_ray.ray.direction = vec_sub(rays->ray.direction, ref_ray.ray.direction);
	normalize(&(ref_ray.ray.direction));
	t_vec color = convert_light(light_effect, obj);
	return (color);
}
