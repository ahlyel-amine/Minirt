/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hooks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:38:10 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/22 04:58:38 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>

void	close_key(int key, t_data *data)
{
	(void)key;
	mlx_destroy_image(data->m_rt->mlx, data->m_rt->mlx_img);
	mlx_destroy_window(data->m_rt->mlx, data->m_rt->mlx_win);
	clearobjs(&data->objects);
	clearlights(&data->light);
	exit(EXIT_SUCCESS);
}

int	m_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clearobjs(&data->objects);
	clearlights(&data->light);
	exit(EXIT_FAILURE);
	return (0);
}

t_hooks_f	hook_func(int idx)
{
	t_hooks_f	func[7];

	*(func) = skip;
	*(func + 1) = close_key;
	*(func + 2) = cam_x;
	*(func + 3) = cam_y;
	*(func + 4) = zoom;
	*(func + 5) = rotate;
	*(func + 6) = scale;
	return (*(func + idx));
}

int	key_hook(int key, t_data *data)
{
	int	indx;

	indx = (key == ESC) * 1 + \
	(key == ARROLEFT || key == ARRORIGHT) * 2 + \
	(key == ARRODOWN || key == ARROUP) * 3 + \
	(key == ZOOMOUT || key == ZOOMIN) * 4;
	hook_func(indx)(key, data);
	data->shape = (key == CKEY) * CYLENDER + (key == PKEY) * PLANE \
	+ (key == SKEY) * SPHERE + \
	(key != SKEY && key != PKEY && key != CKEY) * data->shape;
	indx = (data->shape > 0 && (key == JKEY || key == LKEY || key \
	== IKEY || key == KKEY)) * 5 + (key == KPLUS || key == KMIN) * 6;
	if (indx >= 0 && indx <= 6)
		hook_func(indx)(key, data);
	return (0);
}

void	hooks_settings(t_data *data)
{
	mlx_hook(data->m_rt->mlx_win, 2, (1L >> 0), key_hook, data);
	mlx_hook(data->m_rt->mlx_win, 17, 0L, m_close, data);
}
