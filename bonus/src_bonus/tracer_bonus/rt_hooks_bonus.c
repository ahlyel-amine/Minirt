/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hooks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:38:10 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/17 21:26:29 by aahlyel          ###   ########.fr       */
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

void	zoom(int key, t_data *data)
{
	data->camera.cord.v_z += (key == 69) * 5 - (key == 78) * 5;
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);
}
typedef void (*hooks_f)(int, t_data *);

hooks_f	hook_func(int idx)
{
	hooks_f	func[7];
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
	
	indx = (key == 53) * 1 + (key == 123 || key == 124) * 2 + \
	(key == 125 || key == 126) * 3 + (key == 78 || key == 69) * 4;
	hook_func(indx)(key, data);
	data->shape = (key == 8) * CYLENDER + (key == 35) * PLANE \
	+ (key == 1) * SPHERE + (key != 1 && key != 35 && key != 8) * data->shape;
	indx = (data->shape > 0 && (key == 38 || key == 37 || key \
	== 34 || key == 40)) * 5 + (key == 24 || key == 27) * 6;
	hook_func(indx)(key, data);
	return (0);
}

void	hooks_settings(t_data *data)
{
	mlx_hook(data->m_rt->mlx_win, 2, (1L >> 0), key_hook, data);
	mlx_hook(data->m_rt->mlx_win, 17, 0L, m_close, data);
}
