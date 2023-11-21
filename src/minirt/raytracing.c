/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:38:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/21 19:33:48 by aelbrahm         ###   ########.fr       */
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

int	raytrace(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_light_effect light_effect;
	t_objects	*object;

	object = get_closes_object(&(rays->ray), obj, rec);
	if (!object)
		return (0x0/*0xccaabb*/);
	light_effect = get_light_effect(data, rays, object, rec);
	t_vec color = convert_light(light_effect);
	// nineties(&color);
	// printf("color: %.2f %.2f %.2f\n", color.v_x, color.v_y, color.v_z);
	int rgb = rgb_to_int(color);
	// printf("rgb: %d\n", rgb);
	return (rgb);
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
			my_mlx_put(ptr->m_rt, i, j, raytrace(&ptr->data, &rays, ptr->data.objects, &rec));
		}
	}
	return (NULL);
}
