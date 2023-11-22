/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:38:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/22 16:35:48 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"
#include "draw.h"
#include "vector.h"
#include "tools.h"

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
t_vec	get_ref_ray_color(rec, ray, data, level)
t_hit_record *rec;
t_rays *ray;
t_data *data;
int		level;
{
	t_rays	ref_ray;
	ref_ray.ray.origin = rec->pHit;
	ref_ray.ray.direction = scalar_mult(rec->nHit, 2 * dot_product(ray->ray.direction, rec->nHit));
	ref_ray.ray.direction = vec_sub(ray->ray.direction, ref_ray.ray.direction);
	normalize(&(ref_ray.ray.direction));
	return (raytrace(data, &ref_ray, rec, level));
}

t_vec	raytrace(t_data *data, t_rays *rays, t_hit_record *rec, int level)
{
	t_light_effect light_effect;
	t_objects	*obj;
	rays->closet_obj = get_closes_object(&(rays->ray), data->objects, rec);
	obj = rays->closet_obj;
	if (!rays->closet_obj)
		return ((t_vec){0,0,0}/*0xccaabb*/);
	light_effect = get_light_effect(data, rays, rays->closet_obj, rec);
	level -= 1;
	if (obj->type == SPHERE && level > 0)
	{
		t_rays	ref_ray;
		ref_ray.ray.origin = rec->pHit;
		ref_ray.ray.direction = scalar_mult(rec->nHit, 2 * dot_product(rays->ray.direction, rec->nHit));
		ref_ray.ray.direction = vec_sub(rays->ray.direction, ref_ray.ray.direction);
		normalize(&(ref_ray.ray.direction));
		light_effect.reflect = raytrace(data, &ref_ray, rec, level);
		
	}	
	// nineties(&color);
	// printf("color: %.2f %.2f %.2f\n", color.v_x, color.v_y, color.v_z);
	if (level <= 0)
		obj = NULL;
	t_vec color = convert_light(obj, light_effect);
	// int rgb = rgb_to_int(color);
	// printf("rgb: %d\n", rgb);
	return (color);
}

bool shadow_ray(t_rays *rays, t_light *light, t_objects *obj, t_hit_record *rec)
{
	t_hit_record	h_shadow;
	t_objects		*objt;

	rays->shadow_ray.origin = rec->pHit;
	rays->shadow_ray.direction = vec_sub(light->cord, rec->pHit);
	
	normalize(&(rays->shadow_ray.direction));
	rays->shadow_ray.origin = at(0.01, rays->shadow_ray);
		// printf("origin type : %d\n",obj->type);

	objt = get_closes_object2(&(rays->shadow_ray), obj, &h_shadow);
	// if (objt)
	// 	printf("origin type : %d------type : %d\n",obj->type, objt->type);
	
	return (objt && distance(rec->pHit, light->cord) > h_shadow.t);
}

void	*draw(void *alo)
{
	t_dataset		*ptr;
	t_hit_record	rec;
	t_rays			rays;

	ptr = (t_dataset *)alo;
	ft_memset(&rays, 0, sizeof(t_rays));
	for (int j = ptr->s_y; j < ptr->e_y; j++)
	{
		for (int i = ptr->s_x; i < ptr->e_x; i++)
		{
			Prime_ray(ptr->m_rt, i, j, &(rays.ray), &ptr->data.camera);
			my_mlx_put(ptr->m_rt, i, j, rgb_to_int(raytrace(&ptr->data, &rays, &rec, REF_LEVEL)));
		}
	}
	return (NULL);
}
