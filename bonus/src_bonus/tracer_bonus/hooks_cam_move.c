/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_cam_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 02:50:20 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/24 15:56:58 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "tools_bonus.h"
#include "vector_bonus.h"

void	zoom(int key, t_data *data)
{
	data->camera.cord.v_z += (key == ZOOMIN) * 5 - (key == ZOOMOUT) * 5;
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);
}

void	cam_x(int key, t_data *data)
{
	data->camera.normalized.v_x += ((key == 124) * 0.5) - ((key == 123) * 0.5);
	normalize(&data->camera.normalized);
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);
}

void	cam_y(int key, t_data *data)
{
	data->camera.normalized.v_y += (key == 126) * 0.4 - (key == 125) * 0.4;
	normalize(&data->camera.normalized);
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);
}
