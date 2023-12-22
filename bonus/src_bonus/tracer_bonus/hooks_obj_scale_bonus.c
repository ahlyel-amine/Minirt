/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_obj_scale_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:13:59 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/22 05:48:21 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include "tools_bonus.h"

void	zoom(int key, t_data *data)
{
	data->camera.cord.v_z += (key == ZOOMIN) * 5 - (key == ZOOMOUT) * 5;
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);
}

void	sphere_scale(int key, t_data *data)
{
	t_objects	*obj;

	obj = data->objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			((t_sphere *)obj->object)->diameter += \
			(key == KPLUS) * 0.1 - (key == KMIN) * 0.1;
		obj = obj->next;
	}
}

void	cy_scale(int key, t_data *data)
{
	t_objects	*obj;
	t_cylender	*c;

	obj = data->objects;
	while (obj)
	{
		if (obj->type == CYLENDER)
		{
			c = obj->object;
			((t_cylender *)obj->object)->height += \
			(key == KPLUS) * 0.1 - (key == KMIN) * 0.1;
			calculate_disk_plan(c, c->p_face, true);
			calculate_disk_plan(c, c->p_face->next, false);
		}
		obj = obj->next;
	}
}

t_obj_scale	shape_scale(int idx)
{
	static t_obj_scale	shape_s[2];
	static bool			init;

	if (!init)
	{
		init = true;
		shape_s[0] = sphere_scale;
		shape_s[1] = cy_scale;
	}
	return (*(shape_s + idx));
}

void	scale(int key, t_data *data)
{
	int	idx;

	idx = (data->shape == CYLENDER) * 1;
	shape_scale(idx)(key, data);
	if (!idx && data->counter.sphere)
		make_threads(data->m_rt, *data);
	if (idx && data->counter.cylender)
		make_threads(data->m_rt, *data);
}
