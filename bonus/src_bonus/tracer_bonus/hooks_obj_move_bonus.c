/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_obj_move_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:09:48 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/13 15:24:35 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include "vector_bonus.h"
#include "tools_bonus.h"

void	cam_x(int key, t_data *data)
{
	if (key == 124)
		data->camera.normalized.v_x += 0.5;
	else if (key == 123)
		data->camera.normalized.v_x -= 0.5;
	normalize(&data->camera.normalized);
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);

}

void	cam_y(int key, t_data *data)
{
	if (key == 126)
		data->camera.normalized.v_y += 0.4;
	else if (key == 125)
		data->camera.normalized.v_y -= 0.4;
	normalize(&data->camera.normalized);
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);
}

static void	cylinders_rotate(t_data *data, t_cylender *c, int key)
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
	calculate_disk_plan(c, c->p_face, true);
	calculate_disk_plan(c, c->p_face->next, false);
}

static void	plane_rotate(t_data *data, t_plane *p, int key)
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
	make_threads(data->m_rt, *data);
}
