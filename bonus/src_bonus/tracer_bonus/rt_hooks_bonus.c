/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hooks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:38:10 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/13 15:44:05 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>

void	close_key(t_mrt *scean)
{
	mlx_destroy_image(scean->mlx, scean->mlx_img);
	mlx_destroy_window(scean->mlx, scean->mlx_win);
	exit(EXIT_SUCCESS);
}

int	m_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clearobjs(&data->objects);
	exit(EXIT_FAILURE);
	return (0);
}

void	zoom(int key, t_data *data)
{
	if (key == 69)
		data->camera.cord.v_z += 5;
	else if (key == 78)
		data->camera.cord.v_z -= 5;
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);
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
	if (data->shape && (keycode == 38 || \
	keycode == 37 || keycode == 34 || keycode == 40))
		rotate(keycode, data);
	if ((keycode == 24 || keycode == 27))
		scale(keycode, data);
	return (0);
}

void	hooks_settings(t_data *data)
{
	mlx_hook(data->m_rt->mlx_win, 2, (1L >> 0), key_hook, data);
	mlx_hook(data->m_rt->mlx_win, 17, 0L, m_close, data);
}
