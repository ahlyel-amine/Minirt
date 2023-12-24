/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_obj_move_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:09:48 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/24 00:13:38 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include "vector_bonus.h"
#include "tools_bonus.h"

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

static void	sp_rotate(t_data *data, t_sphere *s, int key)
{
	if (s->spec.texture)
	{
		if (s->rot_x < (M_PI * 0.5) && s->rot_x > -(M_PI * 0.5))
			s->rot_x += (key == LKEY) * (M_PI * 0.01) - \
			(key == JKEY) * (M_PI * 0.01);
		else
			s->rot_x = (M_PI * 0.01);
	}
}

void	rotate(int key, t_data *data)
{
	t_plane		*p;
	t_cylender	*c;
	t_objects	*obj;

	obj = data->objects;
	if (data->shape == CYLENDER && !data->counter.cylender)
		return ;
	if (data->shape == PLANE && !data->counter.plane)
		return ;
	if (data->shape == SPHERE && !data->counter.sphere)
		return ;
	while (obj)
	{
		if (data->shape == CYLENDER && obj->type == CYLENDER)
			cylinders_rotate(data, obj->object, key);
		else if (data->shape == PLANE && obj->type == PLANE)
			plane_rotate(data, obj->object, key);
		else if (data->shape == SPHERE && obj->type == SPHERE \
		&& (obj->texture))
			sp_rotate(data, obj->object, key);
		obj = obj->next;
	}
	lookat(&(data->camera));
	make_threads(data->m_rt, *data);
}
