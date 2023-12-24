/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:00:11 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/23 01:02:36 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "minirt_bonus.h"
#include "vector_bonus.h"
#include "draw_bonus.h"
#include "tools_bonus.h"

t_vec	merge_light(t_vec color, t_color light_color, double ratio)
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

	thita = dot_product(rays->shadow_ray.direction, rec->n_hit);
	diffuse = rec->h_color;
	diffuse = merge_light(diffuse, light->clr, light->brightness * thita);
	return (diffuse);
}

bool	is_specular(t_objects *obj)
{
	t_specular_light	spec;

	spec = get_specular_addr(obj);
	return ((int)spec.intensity == 0 && (int)spec.shininess_factor == 0);
}

t_light_effect	get_light_effect(t_data *data, t_rays *rays, \
t_objects *obj, t_hit_record *rec)
{
	t_light			*lights;
	t_light_effect	effect;
	double			thita;
	bool			inshadow;

	lights = data->light;
	ft_memset(&effect, 0, sizeof(t_light_effect));
	effect.ambient = rec->h_color;
	effect.ambient = merge_light(effect.ambient, \
	data->lighting.clr, data->lighting.ratio);
	while (lights)
	{
		inshadow = shadow_ray(rays, lights, data->objects, rec);
		if (!inshadow)
		{
			effect.diffuse = c_color(effect.diffuse, \
			diffuse_effect(rays, lights, rec), 1, 1);
			if (!is_specular(obj))
				effect.specular = vec_addition(effect.specular, \
				specular_light(rays, lights, get_specular_addr(obj), rec));
		}
		lights = lights->next;
	}
	return (effect);
}

t_vec	convert_light(int level, t_light_effect effect, \
t_objects *obj, t_specular_light refl)
{
	t_vec	res;

	res.v_x = effect.ambient.v_x + effect.diffuse.v_x + effect.specular.v_x;
	res.v_y = effect.ambient.v_y + effect.diffuse.v_y + effect.specular.v_y;
	res.v_z = effect.ambient.v_z + effect.diffuse.v_z + effect.specular.v_z;
	if (level > 0 && refl.reflection > 0)
		res = c_color(res, effect.reflect, \
		1 - refl.reflection, refl.reflection);
	color_range_norm(&res);
	return (res);
}

t_vec	specular_light(t_rays *rays, t_light *light, \
t_specular_light speclr, t_hit_record *rec)
{
	t_vec	specular;
	t_vec	reflect;
	t_vec	view;
	double	spec;
	double	coef;
	double	thita;

	ft_memset(&specular, 0, sizeof(t_vec));
	coef = speclr.shininess_factor;
	view = scalar_mult(scalar_mult(rec->n_hit, 2.0), dot_product(vec_nega(rec->n_hit), rays->shadow_ray.direction));
	reflect = vec_addition(rays->shadow_ray.direction, view);
	thita = dot_product(reflect, view);
	if (thita > EPS)
	{
		spec = pow(thita, speclr.intensity);
		specular = scalar_mult((t_vec){1, 1, 1}, spec);
		specular = merge_light(specular, light->clr, light->brightness * coef);
	}
	else
		return ((t_vec){0,0,0});
	return (specular);
}

