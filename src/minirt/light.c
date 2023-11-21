/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:00:11 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/21 19:32:22 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"
#include "vector.h"
#include "draw.h"
#include "tools.h"

void color_range_norm(t_vec *color)
{
	if (color->v_x > 1)
		color->v_x = 1.0;
	if (color->v_y > 1.0)
		color->v_y = 1.0;
	if (color->v_z > 1.0)
		color->v_z = 1.0;
	if (color->v_x < 0)
		color->v_x = 0.0;
	if (color->v_y < 0)
		color->v_y = 0.0;
	if (color->v_z < 0)
		color->v_z = 0.0;
}

t_vec merge_light(t_vec color, t_color light_color, double ratio)
{
	t_vec res;
	
	res.v_x = color.v_x * ((double)(light_color.r) / 255) * ratio;
	res.v_y = color.v_y * ((double)(light_color.g) / 255) * ratio;
	res.v_z = color.v_z * ((double)(light_color.b) / 255) * ratio;
	color_range_norm(&res);
	// printf("res: %.2f %.2f %.2f\n", res.v_x, res.v_y, res.v_z);
	return (res);
}


t_vec	specular_light(t_rays *rays, t_light *light, t_objects *obj, t_hit_record *rec)
{
	t_vec	specular;
	t_vec	reflect;
	t_vec	view;
	double	spec;
	double	coef;
	double	thita;
	
	coef = 1.0;
	reflect = vec_sub(rays->shadow_ray.direction, scalar_mult(rec->nHit, 2 * dot_product(rays->shadow_ray.direction, rec->nHit)));
	view = vec_sub(rays->ray.direction, scalar_mult(rec->nHit, 2 * dot_product(rays->ray.direction, rec->nHit)));
	thita = dot_product(reflect, view);
	if (thita > eps)
	{
		spec = pow(thita, 10);
		specular = scalar_mult((t_vec){1, 1, 1}, spec);
		specular = merge_light(specular, light->clr, light->brightness * coef);
	}
	else
		specular = (t_vec){1, 1, 1};
	return (specular);
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



t_light_effect	get_light_effect(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_light_effect	effect;
	double			thita;
	ft_memset(&effect, 0, sizeof(t_light_effect));
	effect.ambient = rec->h_color;
	// printf("effect.ambient: %.2f %.2f %.2f\n", effect.ambient.v_x, effect.ambient.v_y, effect.ambient.v_z);
	effect.ambient = merge_light(effect.ambient, data->lighting.clr, data->lighting.ratio);
	t_light *alo = data->light;
	while (alo)
	{
		bool inShadow = shadow_ray(rays, alo, obj, rec);
		if (!inShadow)
		{
			effect.diffuse = c_color(effect.diffuse, diffuse_effect(rays, alo, rec), 1, 1);
			// effect.specular = specular_light(rays, &alo, obj, rec);
			// printf("effect.diffuse: %.2f %.2f %.2f\n", effect.diffuse.v_x, effect.diffuse.v_y, effect.diffuse.v_z);
			}
			alo = alo->next;
	}
	// printf("normal: %.2f %.2f %.2f\n", rec->nHit.v_x, rec->nHit.v_y, rec->nHit.v_z);
	
	return (effect);
}

t_vec	convert_light(t_light_effect effect)
{
	t_vec	res;

	res.v_x = effect.ambient.v_x + effect.diffuse.v_x;
	res.v_y = effect.ambient.v_y + effect.diffuse.v_y;
	res.v_z = effect.ambient.v_z + effect.diffuse.v_z;
	color_range_norm(&res);
	// printf("res: %.2f %.2f %.2f\n", res.v_x, res.v_y, res.v_z);
	return (res);
}
void	nineties(t_vec *color)
{
	color->v_x = MIN(color->v_x, 1.0);
	color->v_y = MIN(color->v_x, 1.0);
	color->v_z = MIN(color->v_x, 1.0);
}
