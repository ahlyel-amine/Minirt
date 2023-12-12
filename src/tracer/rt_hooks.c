/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:38:10 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/12 10:40:22 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"
#include "libft.h"
#include "library.h"
#include "tools.h"
#include <mlx.h>

void	close_key(t_mrt *scean)
{
	mlx_destroy_image(scean->mlx, scean->mlx_img);
	mlx_destroy_window(scean->mlx, scean->mlx_win);
	exit(0);
}
void	cam_x(int key, t_data *data)
{
	if (key == 123)
	{	
		if (data->camera.normalized.v_x < 1.0)
			data->camera.normalized.v_x += 0.2;
	}
	else if (key == 124)
	{
		if (data->camera.normalized.v_x > -1.0)
		data->camera.normalized.v_x -= 0.2;
	}
	if (data->camera.normalized.v_x < 1 && data->camera.normalized.v_x > -1)
	{
		lookat(&(data->camera));
		draw(*data, data->m_rt);
	}
}

void	cam_y(int key, t_data *data)
{
	if (key == 126)
	{	
		if (data->camera.normalized.v_y < 1.0)
			data->camera.normalized.v_y += 0.2;
	}
	else if (key == 125)
	{
		if (data->camera.normalized.v_y > -1.0)
		data->camera.normalized.v_y -= 0.2;
	}
	if (data->camera.normalized.v_y < 1 && data->camera.normalized.v_y > -1)
	{
		lookat(&(data->camera));
		draw(*data, data->m_rt);
	}
}
int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
		close_key(data->m_rt);
	if (keycode == 123 || keycode == 124)
		cam_x(keycode, data);
	if (keycode == 125 || keycode == 126)
		cam_y(keycode, data);
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