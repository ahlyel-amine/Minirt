/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/09 04:55:56 by aelbrahm         ###   ########.fr       */
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

t_coord	ray_color(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
		
	if (obj->type == SPHERE &&  sphere_hit(ray, (t_sphere*)obj->object, rec))
	{
		t_sphere *sphere = (t_sphere *)obj->object;
		t_vec	n = vec_sub(rec->nHit, sphere->cord);
		return (scalar_mult((t_coord){n.v_x + 1, n.v_y + 1, n.v_z + 1}, 0.5));
	}
	else if (obj->type == PLANE && plan_hit(ray, (t_plane*)obj->object, rec))
		return ((t_coord){0.5, 0.5, 0.5});
		
	t_coord	unit_direction = normalized(ray->direction);
	double t = 0.5 * (unit_direction.v_y + 1.0);
	t_coord	c_start = scalar_mult((t_coord){1.0,1.0,1.0}, (1.0 - t));
	t_coord	c_end = scalar_mult((t_coord){0.5, 0.7, 1.0}, t);
	return (scalar_mult((t_coord){0.3,0.3,0.3}, (0.1)));
}
void	get_closes_object(t_rt *m_rt, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_objects	*object;
	double		closest_so_far;
	double		temp;
	t_hit_record	temp_rec;
	
	closest_so_far = M_D;
	object = NULL;
	while (obj)
	{
		if (obj->type == SPHERE && sphere_hit(rays->ray, (t_sphere *)obj->object, &temp_rec))
		{
			temp = temp_rec.t;
			if (temp < closest_so_far && temp > eps)
			{
				closest_so_far = temp;
				object = obj;
				*rec = temp_rec;
			}
		}
		else if (obj->type == PLANE && plan_hit(rays->ray, (t_plane *)obj->object, &temp_rec))
		{
			temp = temp_rec.t;
			if (temp < closest_so_far && temp > eps)
			{
				closest_so_far = temp;
				object = obj;
				*rec = temp_rec;
			}
		}
		obj = obj->next;
	}
	return (object);
}
t_color	raytrace(t_mrt *m_rt, t_rays *rays, t_objects *obj, t_hit_record *rec)
{
	t_light_effect light_effect;
	t_objects	*object;
	
	object = get_closes_object(m_rt, rays, obj, rec);
	if (!object)
		return ((t_color){0, 0, 0});
	light_effect = get_light_effect(m_rt, rays, object, rec);
	
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
	while (data.objects->type != SPHERE)
		data.objects = data.objects->next;
	t_sphere *sphere = (t_sphere *)data.objects->object;
	// t_plane *plan = (t_plane *)data.objects->object;
	// printf("%.2f\n", sphere->diameter);
	printf("%.2f %.2f %.2f\n", (float)((sphere->clr.r))/(255), (float)(sphere->clr.g/255), (float)(sphere->clr.b/255));
	double coef = 1.0;
	t_light light = data.light;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Prime_ray(m_rt, i, j, rays->ray, cam);
			
		}
	}
	// // t_camera *cam = (t_camera *)data->objects->object;
	// // lookat(m_rt->cam_matrix, m_rt, cam);	
	// y = HEIGHT;
	// while (y--)
	// {
	// 	x = 0;
	// 		// double pxY = (HEIGHT - y - 0.5) / HEIGHT;
	// 	while (x < WIDTH)
	// 	{
	// 		// puts("alo");
	// 		Prime_ray(m_rt, x, y, ray, cam);
	// 		t_vec pHit, nHit;
	// 		double minDistance = INFINITY;
	// 		if (sphere_intersect(*sphere, *ray, &pHit, &nHit))
	// 			my_mlx_put(m_rt, x, y, 0xffe);
	// 		else
	// 			my_mlx_put(m_rt, x, y, 0xffff);
			
	// 		// printf("%.8f  %.8f %.8f\n", ray->direction.v_x, ray->direction.v_x, ray->direction.v_x);
	// 		// usleep(10000);
	// 		x++;
	// 	}
	// }
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
