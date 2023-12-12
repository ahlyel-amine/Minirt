/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:38:10 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/12 12:15:16 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"
#include "libft.h"
#include "library.h"
#include "tools.h"
#include "vector.h"
#include <mlx.h>

void	close_key(t_mrt *scean)
{
	mlx_destroy_image(scean->mlx, scean->mlx_img);
	mlx_destroy_window(scean->mlx, scean->mlx_win);
	exit(0);
}
void	cam_x(int key, t_data *data)
{
	if (key == 124)
		data->camera.normalized.v_x += 0.5;
	else if (key == 123)
		data->camera.normalized.v_x -= 0.5;
	normalize(&data->camera.normalized);
	lookat(&(data->camera));
	draw(*data, data->m_rt);
}

void	cam_y(int key, t_data *data)
{
	if (key == 126)
			data->camera.normalized.v_y += 0.4;
	else if (key == 125)
		data->camera.normalized.v_y -= 0.4;
	normalize(&data->camera.normalized);
	lookat(&(data->camera));
	draw(*data, data->m_rt);
}
void	zoom(int key, t_data *data)
{
	if (key == 69)
			data->camera.cord.v_z += 5;
	else if (key == 78)
			data->camera.cord.v_z -= 5;
	lookat(&(data->camera));
	draw(*data, data->m_rt);
}

void	cylinders_rotate(t_data *data, t_cylender *c, int key)
{
	if (key == 38)
		c->normalized.v_x += 0.5;
	else if (key == 37)
		c->normalized.v_x -= 0.5;
	else if (key == 34)
		c->normalized.v_z += 0.5;
	else if (key == 40)
		c->normalized.v_z -= 0.5;
	normalize(&c->normalized);
}
void	plane_rotate(t_data *data, t_plane *p, int key)
{
	if (key == 38)
		p->normalized.v_x += 0.1;
	else if (key == 37)
		p->normalized.v_x -= 0.1;
	else if (key == 34)
		p->normalized.v_y += 0.1;
	else if (key == 40)
		p->normalized.v_y -= 0.1;
	normalize(&p->normalized);
}
void	rotate(int key, t_data *data)
{
	t_plane		*p;
	t_cylender	*c;
	t_objects	*obj;

	obj = data->objects;
	while (obj)
	{
		if (data->shape == CYLENDER && obj->type == CYLENDER)
			cylinders_rotate(data, obj->object, key);
		else if (data->shape == PLANE && obj->type == PLANE)
			plane_rotate(data, obj->object, key);
		obj = obj->next;	
	}
	lookat(&(data->camera));
	draw(*data, data->m_rt);
}
void	sphere_scale(t_data *data, int key)
{
	t_objects *obj;

	obj = data->objects;
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			if (key == 27)
				((t_sphere *)obj->object)->diameter -= 0.1;
			else if (key == 24)
				((t_sphere *)obj->object)->diameter += 0.1;
		}
		obj = obj->next;
	}
}

void	cy_scale(t_data *data, int key)
{
	t_objects *obj;

	obj = data->objects;
	while (obj)
	{
		if (obj->type == CYLENDER)
		{
			if (key == 27)
				((t_cylender *)obj->object)->height -= 0.1;
			else if (key == 24)
				((t_cylender *)obj->object)->height += 0.1;
		}
		obj = obj->next;
	}
}

void	scale(int key, t_data *data)
{
	if (data->shape == SPHERE)
		sphere_scale(data, key);
	else if (data->shape == CYLENDER)
		cy_scale(data, key);
	draw(*data, data->m_rt);
}
int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
		close_key(data->m_rt);
	if (keycode == 123 || keycode == 124)
		cam_x(keycode, data);
	if (keycode == 125 || keycode == 126)
		cam_y(keycode, data);
	if (keycode == 78 || keycode == 69)
		zoom(keycode, data);
	if (keycode == 8)
		data->shape = CYLENDER;
	if (keycode == 35)
		data->shape = PLANE;
	if (keycode == 1)
		data->shape = SPHERE;
	if (data->shape && (keycode == 38 || keycode == 37 || keycode == 34 || keycode == 40))
		rotate(keycode, data);
	if ((keycode == 24 || keycode == 27))
		scale(keycode, data);
	printf("%d\n", keycode);
	return (0);
}
int m_close(void *param)
{
	t_data	*data;
	data = (t_data *)param;
	clearobjs(&data->objects);
	exit(EXIT_FAILURE);
	return (0);
}
void	hooks_settings(t_data *data)
{
	mlx_hook(data->m_rt->mlx_win, 2, (1L >> 0), key_hook, data);
	mlx_hook(data->m_rt->mlx_win, 17, 0L, m_close, data);
}