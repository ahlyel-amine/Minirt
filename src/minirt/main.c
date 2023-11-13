/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/13 05:20:37 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"
#include "vector.h"

#include <mlx.h>
#define WIDTH 1280
#define HEIGHT 820
#define FRAME 3
#define M_D 1.79769e+308
#define eps 1e-3



void	clearobjs(t_objects **lst)
{
	t_objects	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free ((*lst)->object);
		free(*lst);
		*lst = tmp;
	}
}

void	my_mlx_put(t_mrt *rt, int x, int y, int color)
{
	int	iter;

	if (x < (WIDTH - FRAME) && x >= FRAME && y >= FRAME && y < (HEIGHT - FRAME))
	{
		iter = (x * rt->bit_per_px / 8) + (y * rt->line_len);
		// printf("rt->bit_per_px: %d rt->line_len: %d\n", rt->bit_per_px, rt->line_len);
		rt->mlx_add[iter] = color;
		rt->mlx_add[++iter] = (color >> 8) & 0xFF;
		rt->mlx_add[++iter] = (color >> 16) & 0xFF;
	}
	return ;
}

int	get_pixel(t_mrt *rt, int x, int y)
{
	int	iter;
	int	color;

	if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
	{
		iter = (x * rt->bit_per_px / 8) + (y * rt->line_len);
		color = rt->mlx_add[iter];
		color |= rt->mlx_add[++iter] << 8;
		color |= rt->mlx_add[++iter] << 16;
		return (color);
	}
	return (0);
}

int	rgb_to_int(t_coord color)
{
	int	r;
	int	g;
	int	b;
	
	r = (int)(255.0 * (color.v_x));
	g = (int)(255.0 * (color.v_y));
	b = (int)(255.0 * color.v_z);
	return (r << 16 | g << 8 | b);
}

// t_coord	ray_color(t_ray *ray, t_objects *obj, t_hit_record *rec)
// {
		
// 	if (obj->type == SPHERE &&  sphere_hit(ray, (t_sphere*)obj->object, rec))
// 	{
// 		t_sphere *sphere = (t_sphere *)obj->object;
// 		t_vec	n = vec_sub(rec->nHit, sphere->cord);
// 		return (scalar_mult((t_coord){n.v_x + 1, n.v_y + 1, n.v_z + 1}, 0.5));
// 	}
// 	else if (obj->type == PLANE && plan_hit(ray, (t_plane*)obj->object, rec))
// 		return ((t_coord){0.5, 0.5, 0.5});
		
// 	t_coord	unit_direction = normalized(ray->direction);
// 	double t = 0.5 * (unit_direction.v_y + 1.0);
// 	t_coord	c_start = scalar_mult((t_coord){1.0,1.0,1.0}, (1.0 - t));
// 	t_coord	c_end = scalar_mult((t_coord){0.5, 0.7, 1.0}, t);
// 	return (scalar_mult((t_coord){0.3,0.3,0.3}, (0.1)));
// }
t_objects	*get_closes_object(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_objects	*object;
	double		closest_so_far;
	double		temp;
	t_hit_record	temp_rec;
	closest_so_far = INFINITY;
	object = NULL;

	while (obj)
	{
		if (intersect(obj->type)(ray, obj, &temp_rec))
		{
			temp = temp_rec.t;
			if (temp < closest_so_far)
			{
				closest_so_far = temp;
				object = obj;
				*rec = temp_rec;
			}
		}
		obj = obj->next;
	}
	// if (object)
	// {
	// 	if (object->type == SPHERE)
	// 		rec->h_color = (t_vec){(double)(((t_sphere *)object->object)->clr.r) / 255, (double)(((t_sphere *)object->object)->clr.g) / 255, (double)(((t_sphere *)object->object)->clr.b) / 255};
	// 	else if (object->type == PLANE)
	// 		rec->h_color = (t_vec){(double)(((t_plane *)object->object)->clr.r) / 255, (double)(((t_plane *)object->object)->clr.g) / 255, (double)(((t_plane *)object->object)->clr.b) / 255};
	// }
	return (object);
}
t_vec merge_light(t_vec color, t_color light_color, double ratio)
{
	t_vec res;
	
	res.v_x = color.v_x * ((double)(light_color.r) / 255) * ratio;
	res.v_y = color.v_y * ((double)(light_color.g) / 255) * ratio;
	res.v_z = color.v_z * ((double)(light_color.b) / 255) * ratio;
	if (res.v_x > 1)
		res.v_x = 1;
	if (res.v_y > 1)
		res.v_y = 1;
	if (res.v_z > 1)
		res.v_z = 1;
	if (res.v_x <= 0.0)
		res.v_x = 0.0;
	if (res.v_y <= 0.0)
		res.v_y = 0.0;
	if (res.v_z <= 0.0)
		res.v_z = 0.0;
	// printf("res: %.2f %.2f %.2f\n", res.v_x, res.v_y, res.v_z);
	return (res);
}


bool shadow_ray(t_rays *rays, t_light *light, t_objects *obj, t_hit_record *rec)
{
	t_hit_record	h_shadow;
	t_objects		*objt;

	rays->shadow_ray.origin = rec->pHit;
	rays->shadow_ray.direction = vec_sub(light->cord, rec->pHit);
	
	normalize(&rays->shadow_ray.direction);
	rays->shadow_ray.origin = at(0.01, rays->shadow_ray);
	objt = get_closes_object(&(rays->shadow_ray), obj, &h_shadow);
	
	return (objt);
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

t_light_effect	get_light_effect(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_light_effect	effect;
	double			thita;
	ft_memset(&effect, 0, sizeof(t_light_effect));
	effect.ambient = rec->h_color;
	// printf("effect.ambient: %.2f %.2f %.2f\n", effect.ambient.v_x, effect.ambient.v_y, effect.ambient.v_z);
	effect.ambient = merge_light(effect.ambient, data->lighting.clr, data->lighting.ratio);
	bool inShadow = shadow_ray(rays, &data->light, obj, rec);
	// printf("normal: %.2f %.2f %.2f\n", rec->nHit.v_x, rec->nHit.v_y, rec->nHit.v_z);
	// if (!inShadow)
	// {
	// 	effect.diffuse = rec->h_color;
	// 	thita = dot_product(rec->nHit, rays->shadow_ray.direction);
	// 	effect.diffuse = merge_light(effect.diffuse, data->light.clr, data->light.brightness * thita);
	// 	// effect.specular = specular_light(rays, &data->light, obj, rec);
	// }
	
	return (effect);
}

t_vec	convert_light(t_light_effect effect)
{
	t_vec	res;
	res.v_x = effect.ambient.v_x + effect.diffuse.v_x;
	res.v_y = effect.ambient.v_y + effect.diffuse.v_y;
	res.v_z = effect.ambient.v_z + effect.diffuse.v_z;
	// printf("res: %.2f %.2f %.2f\n", res.v_x, res.v_y, res.v_z);

	return (res);
}

int	raytrace(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_light_effect light_effect;
	t_objects	*object;
	// if (obj)
	// 	printf("--object-type: %d--\n", object->type);

	object = get_closes_object(&(rays->ray), obj, rec);
	static int i;
	if (!object)
	{
		t_coord	unit_direction = normalized(rays->ray.direction);
		double t = 0.5 * (unit_direction.v_y + 1.0);
		t_coord	c_start = scalar_mult((t_coord){1.0,1.0,1.0}, (1.0 - t));
		t_coord	c_end = scalar_mult((t_coord){0.5, 0.7, 0.2}, t);
		return (rgb_to_int(scalar_mult(c_end, 1)));
	}
	// printf("object-type: %d -%d-\n", object->type, i++);
	light_effect = get_light_effect(data, rays, object, rec);
	int rgb = rgb_to_int(convert_light(light_effect));
	return (rgb);
}

void	draw(t_mrt *m_rt, t_rays *rays, t_camera *cam, t_data data)
{
	int	x;
	int	y;
	int	nx = WIDTH;
	int ny = HEIGHT;
	t_hit_record	rec;
	bool inShadow;
	lookat(m_rt, cam);
	double coef = 1.0;
	t_light light = data.light;
	t_objects *obj = data.objects;
	for (int j = 0; j < ny; j++)
	{
		for (int i = 0; i < nx; i++)
		{
			Prime_ray(m_rt, i, j, &(rays->ray), cam);
			my_mlx_put(m_rt, i, j, raytrace(&data, rays, obj, &rec));
		}
	}
	// // t_camera *cam = (t_camera *)data->objects->object;

	mlx_put_image_to_window(m_rt->mlx, m_rt->mlx_win, m_rt->mlx_img, 0, 0);
}

int main(int ac, char **av)
{
	t_data	data;
	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (!parcer(av[1], &data))
			return (clearobjs(&data.objects),  1);
		print_scean(data);
		printf("sphers:%d cylenders:%d planes:%d\n", data.counter.sphere, data.counter.cylender, data.counter.plane);
		t_mrt scean;
		t_rays rays;
		ft_memset(&rays, 0, sizeof(t_rays));
		scean.mlx = mlx_init();
		scean.mlx_win = mlx_new_window(scean.mlx, WIDTH, HEIGHT, "MINI_RT");
		scean.mlx_img = mlx_new_image(scean.mlx, WIDTH, HEIGHT);
		scean.mlx_add = mlx_get_data_addr(scean.mlx_img, &(scean.bit_per_px), &(scean.line_len), &(scean.endian));
		draw(&scean, &rays, &data.camera, data);
		mlx_loop(scean.mlx);
	}
	return 0;
}
