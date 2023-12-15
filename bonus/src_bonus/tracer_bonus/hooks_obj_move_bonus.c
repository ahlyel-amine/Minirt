/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_obj_move_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:09:48 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/14 12:25:29 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include "vector_bonus.h"
#include "tools_bonus.h"

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

static void	cylinders_rotate(t_data *data, t_cylender *c, int key)
{
	c->normalized.v_x += (key == 38) * 0.5 - (key == 37) * 0.5;
	c->normalized.v_z += (key == 34) * 0.5 - (key == 40) * 0.5;
	normalize(&c->normalized);
	calculate_disk_plan(c, c->p_face, true);
	calculate_disk_plan(c, c->p_face->next, false);
}

static void	plane_rotate(t_data *data, t_plane *p, int key)
{
	p->normalized.v_x += (key == 38) * 0.1 - (key == 37) * 0.1;
	p->normalized.v_y += (key == 34) * 0.1 - (key == 40) * 0.1;
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
	make_threads(data->m_rt, *data);
}
