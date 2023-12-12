/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:00:11 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/12 09:05:06 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"
#include "vector.h"
#include "draw.h"
#include "tools.h"

t_vec merge_light(t_vec color, t_color light_color, double ratio)
{
	t_vec	res;
	
	res.v_x = color.v_x * ((double)(light_color.r) / 255) * ratio;
	res.v_y = color.v_y * ((double)(light_color.g) / 255) * ratio;
	res.v_z = color.v_z * ((double)(light_color.b) / 255) * ratio;
	color_range_norm(&res);
	return (res);
}

t_vec	diffuse_effect(t_rays *rays, t_light *light, t_hit_record *rec)
{
	t_vec	diffuse;
	double	thita;
	
	thita = dot_product(rays->shadow_ray.direction, rec->nHit);
	diffuse = rec->h_color;
	diffuse = merge_light(diffuse, light->clr, light->brightness * thita);
	return (diffuse);
}

t_light_effect	get_light_effect(data, rays, rec)
t_data *data;
t_rays *rays;
t_hit_record *rec;
{
	t_light_effect	effect;
	double			thita;

	ft_memset(&effect, 0, sizeof(t_light_effect));
	effect.ambient = rec->h_color;
	effect.ambient = merge_light(effect.ambient, data->lighting.clr, data->lighting.ratio);
	if (!shadow_ray(rays, &data->light, data->objects, rec))
		effect.diffuse = c_color(effect.diffuse, diffuse_effect(rays, &data->light, rec), 1, 1);
	return (effect);
}

t_vec	convert_light(t_light_effect effect, t_objects *obj)
{
	t_vec	res;

	res.v_x = effect.ambient.v_x + effect.diffuse.v_x;
	res.v_y = effect.ambient.v_y + effect.diffuse.v_y;
	res.v_z = effect.ambient.v_z + effect.diffuse.v_z;
	color_range_norm(&res);
	return (res);
}
