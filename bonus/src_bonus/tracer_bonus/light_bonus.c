/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 01:00:11 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/11 01:29:54 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "minirt_bonus.h"
#include "vector_bonus.h"
#include "draw_bonus.h"
#include "tools_bonus.h"

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

t_light_effect	get_light_effect(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_light_effect	effect;
	double			thita;
	t_light *lights;
	bool inShadow;

	lights = data->light;
	ft_memset(&effect, 0, sizeof(t_light_effect));
	effect.ambient = rec->h_color;
	effect.ambient = merge_light(effect.ambient, data->lighting.clr, data->lighting.ratio);
	while (lights)
	{
		inShadow = shadow_ray(rays, lights, obj, rec);
		if (!inShadow)
		{
			effect.diffuse = c_color(effect.diffuse, diffuse_effect(rays, lights, rec), 1, 1);
			effect.specular =  vec_addition(effect.specular, specular_light(rays, lights, get_specular_addr(obj), rec));
		}	
		lights = lights->next;
	}
	return (effect);
}

t_vec	convert_light(int level, t_light_effect effect, t_objects *obj, t_specular_light refl)
{
	t_vec	res;

	res.v_x = effect.ambient.v_x + effect.diffuse.v_x + effect.specular.v_x;
	res.v_y = effect.ambient.v_y + effect.diffuse.v_y + effect.specular.v_y;
	res.v_z = effect.ambient.v_z + effect.diffuse.v_z + effect.specular.v_z;
	if (level > 0 && refl.reflection > 0)
		res = c_color(res, effect.reflect, 1 - refl.reflection, refl.reflection);
	color_range_norm(&res);
	return (res);
}

t_vec	specular_light(t_rays *rays, t_light *light, t_specular_light speclr, t_hit_record *rec)
{
	t_vec	specular;
	t_vec	reflect;
	t_vec	view;
	double	spec;
	double	coef;
	double	thita;

	ft_memset(&specular, 0, sizeof(t_vec));
	coef = speclr.shininess_factor;
	view = scalar_mult(scalar_mult(rec->nHit, 2.0), dot_product(vec_nega(rec->nHit), rays->shadow_ray.direction));
	reflect = vec_addition(rays->shadow_ray.direction, view);
	thita = dot_product(reflect, view);
	if (thita > eps)
	{
		spec = pow(thita, speclr.intensity);
		specular = scalar_mult((t_vec){1, 1, 1}, spec);
		specular = merge_light(specular, light->clr, light->brightness * coef);
	}
	else
		return ((t_vec){0,0,0});
	return (specular);
}

void	nineties(t_vec *color)
{
	color->v_x = MIN(color->v_x, 1.0);
	color->v_y = MIN(color->v_x, 1.0);
	color->v_z = MIN(color->v_x, 1.0);
}
// #include <stdio.h>
// #include <math.h>

// // Structure to represent a 3D vector
// typedef struct {
//     float x, y, z;
// } Vector3;

// // Structure to represent a point on the surface hit by a ray
// typedef struct {
//     Vector3 position;  // Hit point coordinates
//     Vector3 normal;    // Surface normal at the hit point
//     float u, v;        // UV coordinates on the surface
// } HitPoint;

// // Bump mapping function
// void bumpMap(HitPoint *hit, float bumpiness) {
//     // Simulate the derivative by finding the difference in texture color
//     // For simplicity, we'll use a basic grayscale texture with values in the range [0, 1]
//     float textureColorAtHitPoint = /* ... (get texture color at hit->u, hit->v) ... */;
//     float textureColorAtNeighbor = /* ... (get texture color at neighboring UV coordinates) ... */;

//     // Calculate the bump amount based on the difference in texture color
//     float bumpAmount = (textureColorAtNeighbor - textureColorAtHitPoint) * bumpiness;

//     // Adjust the surface normal based on the bump amount
//     hit->normal.x += bumpAmount;
//     hit->normal.y += bumpAmount;
//     hit->normal.z += bumpAmount;

//     // Normalize the modified normal to maintain it as a unit vector
//     float normalMagnitude = sqrt(hit->normal.x * hit->normal.x + hit->normal.y * hit->normal.y + hit->normal.z * hit->normal.z);
//     hit->normal.x /= normalMagnitude;
//     hit->normal.y /= normalMagnitude;
//     hit->normal.z /= normalMagnitude;
// }

// int main() {
//     // Example usage of bump mapping
//     HitPoint hit;
//     hit.position.x = 1.0;
//     hit.position.y = 2.0;
//     hit.position.z = 3.0;
//     hit.normal.x = 0.0;
//     hit.normal.y = 0.0;
//     hit.normal.z = 1.0;
//     hit.u = 0.5;
//     hit.v = 0.5;

//     // Apply bump mapping with a bumpiness factor
//     bumpMap(&hit, 0.1);

//     // The hit structure now contains the modified normal after bump mapping
//     printf("Modified Normal: (%f, %f, %f)\n", hit.normal.x, hit.normal.y, hit.normal.z);

//     return 0;
// }

// // Assuming you have a 2D texture represented by a 2D array or image data
// float textureColorAtHitPoint = getGrayscaleTextureColor(texture, hit->u, hit->v);

// // Function to get grayscale texture color at given UV coordinates
// float getGrayscaleTextureColor(float texture[][width], float u, float v) {
//     // Assuming 'width' is the width of the texture
//     // Perform bilinear interpolation to get the texture color
//     int x = (int)(u * (width - 1));
//     int y = (int)(v * (height - 1));

//     // Bilinear interpolation
//     float uRatio = u * (width - 1) - x;
//     float vRatio = v * (height - 1) - y;
//     float uOpposite = 1.0 - uRatio;
//     float vOpposite = 1.0 - vRatio;

//     float color = uOpposite * vOpposite * texture[y][x] +
//                   uRatio * vOpposite * texture[y][x + 1] +
//                   uOpposite * vRatio * texture[y + 1][x] +
//                   uRatio * vRatio * texture[y + 1][x + 1];

//     return color;
// }
