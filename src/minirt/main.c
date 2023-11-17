/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/17 03:42:53 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"
#include "vector.h"
#include <pthread.h>
#include <mlx.h>

#define FRAME 3
#define M_D 1.79769e+308
#define eps 1e-3


typedef struct s_dataset
{
	t_mrt *m_rt;
	t_rays *rays;
	t_camera *cam;
	t_data data;
	int s_x;
	int s_y;
	int e_x;
	int e_y;
}	t_dataset;

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
		if (intersect(obj->type)(ray, obj, &temp_rec) && temp_rec.t > eps && temp_rec.t < closest_so_far)
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

t_objects	*get_closes_object2(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_objects	*object;
	double		closest_so_far;
	double		temp;
	t_hit_record	temp_rec;
	closest_so_far = INFINITY;
	object = NULL;

	while (obj)
	{
		if (obj->type != PLANE && intersect(obj->type)(ray, obj, &temp_rec))
		{
			temp = temp_rec.t;
			if (temp < closest_so_far)
			{
				closest_so_far = temp;
				object = obj;
				*rec = temp_rec;
				return obj;
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
void	nineties(t_vec *color)
{
	color->v_x = MIN(color->v_x, 1.0);
	color->v_y = MIN(color->v_x, 1.0);
	color->v_z = MIN(color->v_x, 1.0);
}
void color_range_norm(t_vec *color)
{
	if (color->v_x > 1)
		color->v_x = 1.0;
	if (color->v_y > 1.0)
		color->v_y = 1.0;
	if (color->v_z > 1.0)
		color->v_z = 1.0;
}
t_vec merge_light(t_vec color, t_color light_color, double ratio)
{
	t_vec res;

	res.v_x = color.v_x * ((double)(light_color.r) / 255) * ratio;
	res.v_y = color.v_y * ((double)(light_color.g) / 255) * ratio;
	res.v_z = color.v_z * ((double)(light_color.b) / 255) * ratio;
	// nineties(&res); //black and withe
	color_range_norm(&res);
	// printf("res: %.2f %.2f %.2f\n", res.v_x, res.v_y, res.v_z);
	return (res);
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
	// printf("thita: %.2f\n", thita);
	// if (thita < eps)
	// 	thita = 0;
	diffuse = rec->h_color;
		diffuse = merge_light(diffuse, light->clr, light->brightness * thita);
	return (diffuse);
}
t_vec	c_color(t_vec f_c, t_vec s_c, double p1, double p2)
{
	t_vec r_color;
	r_color.v_x = f_c.v_x * p1 + s_c.v_x * p2;
	r_color.v_y = f_c.v_y * p1 + s_c.v_y * p2;
	r_color.v_z = f_c.v_z * p1 + s_c.v_z * p2;
	color_range_norm(&r_color);
	return (r_color);
}
t_light_effect	get_light_effect(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_light_effect	effect;
	double			thita;
	ft_memset(&effect, 0, sizeof(t_light_effect));
	effect.ambient = rec->h_color;
	t_vec dis =vec_sub(data->light.cord, rec->pHit);
	effect.ambient = merge_light(effect.ambient, data->lighting.clr, data->lighting.ratio);
	bool inShadow = shadow_ray(rays, &data->light, data->objects, rec);
	if (!inShadow)
	{
		effect.diffuse = c_color(effect.diffuse, diffuse_effect(rays, &data->light, rec), 1, 1);
	}
	
	return (effect);
}

t_vec	convert_light(t_light_effect effect)
{
	t_vec	res;
	res.v_x = effect.ambient.v_x + effect.diffuse.v_x;
	res.v_y = effect.ambient.v_y + effect.diffuse.v_y;
	res.v_z = effect.ambient.v_z + effect.diffuse.v_z;
	color_range_norm(&res);
	return (res);
}

int	raytrace(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_light_effect light_effect;
	t_objects	*object;

	ft_memset(&light_effect, 0, sizeof(t_light_effect));
	object = get_closes_object(&(rays->ray), obj, rec);
	
	if (!object)
	{
		// t_coord	unit_direction = normalized(rays->ray.direction);
		// double t = 0.5 * (unit_direction.v_y + 1.0);
		// t_coord	c_start = scalar_mult((t_coord){1.0,1.0,1.0}, (1.0 - t));
		// t_coord	c_end = scalar_mult((t_coord){0.5, 0.7, 0.2}, t);
		// return (rgb_to_int(scalar_mult(c_end, 1)));
		return (0x00);
	}
	light_effect = get_light_effect(data, rays, object, rec);
	t_vec color = convert_light(light_effect);
	nineties(&color);
	// int rgb = rgb_to_int(color);
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
	mlx_put_image_to_window(m_rt->mlx, m_rt->mlx_win, m_rt->mlx_img, 0, 0);
}
void	*draw2(void *alo)
{
	t_dataset		*ptr;
	t_hit_record	rec;

	ptr = (t_dataset *)alo;
	lookat(ptr->m_rt, ptr->cam);
	for (int j = ptr->s_y; j < ptr->e_y; j++)
	{
		for (int i = ptr->s_x; i < ptr->e_x; i++)
		{
			Prime_ray(ptr->m_rt, i, j, &(ptr->rays->ray), ptr->cam);
			my_mlx_put(ptr->m_rt, i, j, raytrace(&ptr->data, ptr->rays, ptr->data.objects, &rec));
		}
	}
	return (NULL);
}
int main(int ac, char **av)
{
	t_data	data;
	pthread_t	th[10];
	t_dataset ptr[10];
	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (!parcer(av[1], &data))
			return (clearobjs(&data.objects),  1);
		
		print_scean(data);
		printf("sphers:%d cylenders:%d planes:%d\n", data.counter.sphere, data.counter.cylender, data.counter.plane);
		t_mrt scean[10];
		t_mrt scean2;
		t_rays rays[10];
		ft_memset(&rays, 0, sizeof(t_rays));
		scean[0].mlx = mlx_init();
		scean[0].mlx_win = mlx_new_window(scean[0].mlx, WIDTH, HEIGHT, "MINI_RT");
		scean[0].mlx_img = mlx_new_image(scean[0].mlx, WIDTH, HEIGHT);
		int coef = 0;
		int coef_y = 0;
		for (int i = 0; i < 10; i++) {
			scean[i].mlx = scean[0].mlx;
			scean[i].mlx_win = scean[0].mlx_win;
			scean[i].mlx_img = scean[0].mlx_img;
			scean[i].mlx_add = mlx_get_data_addr(scean[i].mlx_img, &(scean[i].bit_per_px), &(scean[i].line_len), &(scean[i].endian));
			ptr[i].m_rt = &scean[i];
			ptr[i].rays = &rays[i];
			ptr[i].cam = &data.camera;
			ptr[i].data = data;
			ptr[i].s_x = (coef * WIDTH / 5);
			ptr[i].e_x = ((coef + 1) * WIDTH / 5);
			ptr[i].s_y = (coef_y * HEIGHT / 2);
			ptr[i].e_y = ((coef_y + 1) * HEIGHT / 2);
			if (i % 2) {
				coef_y = 0;
				coef++;
			}
			else
				coef_y++;
			pthread_create(&th[i], NULL, draw2, &ptr[i]);
		}
		for (int i = 0; i < 10; i++){
			pthread_join(th[i], NULL);
		}
		mlx_put_image_to_window(scean[0].mlx, scean[0].mlx_win, scean[0].mlx_img, 0, 0);
		mlx_loop(scean[0].mlx);
	}
	return 0;
}