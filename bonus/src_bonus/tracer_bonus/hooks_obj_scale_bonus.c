/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_obj_scale_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:13:59 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/22 00:01:28 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include "tools_bonus.h"

void	sphere_scale(int key, t_data *data)
{
	t_objects	*obj;

	obj = data->objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			((t_sphere *)obj->object)->diameter += \
			(key == 24) * 0.1 - (key == 27) * 0.1;
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
			(key == 24) * 0.1 - (key == 27) * 0.1;
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

	idx = (data->shape == SPHERE) * 1 + (data->shape == CYLENDER) * 2;
	if (!idx)
	{
		shape_scale(idx)(key, data);
		make_threads(data->m_rt, *data);
	}
}
