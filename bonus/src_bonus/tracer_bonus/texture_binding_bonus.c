/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_binding_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 03:17:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/22 06:37:44 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library_bonus.h"
#include "vector_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include <stdlib.h>

double	get_cscale_texture(t_texture_img *bump, int x, int y)
{
	int		index;
	double	grey;
	t_vec	color;

	index = (x * bump->bpp / 8) + (y * bump->line_len);
	color.v_x = (unsigned char)bump->addr[abs(index) + 2] / 255.0;
	color.v_y = (unsigned char)bump->addr[abs(index) + 1] / 255.0;
	color.v_z = (unsigned char)bump->addr[abs(index)] / 255.0;
	grey = color.v_x + color.v_y * 255.0 + color.v_z;
	return (grey);
}

bool	sphere_bump(t_hit_record *rec, t_sphere *sphere)
{
	t_vec		perp_u;
	t_vec		perp_v;
	t_bump_data	b;

	if (!sphere->spec.bump || !sphere->bump)
		return (false);
	get_uv_sphere(sphere, rec, &b.u, &b.v);
	b.axis = (t_vec){0, 0, 1};
	b.x = ((int)(b.u * (sphere->bump->width - 1)));
	b.y = (((1 - b.v) * (sphere->bump->height - 1)));
	b.u = get_cscale_texture(sphere->bump, b.x, b.y);
	b.v = get_cscale_texture(sphere->bump, (b.x + 1) % \
	sphere->bump->width, b.y);
	b.b_scale_u = (b.u - b.v) * -0.2;
	b.v = get_cscale_texture(sphere->bump, b.x, (b.y + 1) % \
	sphere->bump->height);
	b.b_scale_v = (b.u - b.v) * -0.2;
	perp_u = cross_product(rec->n_hit, b.axis);
	perp_v = cross_product(rec->n_hit, perp_u);
	rec->n_hit = vec_addition(rec->n_hit, \
	scalar_mult(perp_u, b.b_scale_v));
	rec->n_hit = vec_addition(rec->n_hit, \
	scalar_mult(perp_v, b.b_scale_u));
	return (true);
}

bool	plane_bump(t_hit_record *rec, t_plane *plane)
{
	t_vec		perp_u;
	t_vec		perp_v;
	t_bump_data	b;

	if (!plane->spec.bump || !plane->bump)
		return (false);
	get_uv_plane(plane, rec, &b.u, &b.v);
	b.axis = normalized(plane->normalized);
	b.x = ((int)(b.u * (plane->bump->width - 1)) % plane->bump->width);
	b.y = (int)((1 - b.v) * (plane->bump->height - 1)) % plane->bump->height;
	b.u = get_cscale_texture(plane->bump, b.x, b.y);
	b.v = get_cscale_texture(plane->bump, \
	(b.x + 1) % plane->bump->width, b.y);
	b.b_scale_u = (b.u - b.v) * -0.05;
	b.v = get_cscale_texture(plane->bump, \
	b.x, (b.y + 1) % plane->bump->height);
	b.b_scale_v = (b.u - b.v) * -0.05;
	perp_u = cross_product(rec->n_hit, b.axis);
	perp_v = cross_product(rec->n_hit, perp_u);
	rec->n_hit = vec_addition(rec->n_hit, \
	create_vec_from_scalar(perp_u, b.b_scale_u));
	rec->n_hit = vec_addition(rec->n_hit, \
	create_vec_from_scalar(perp_v, b.b_scale_v));
	return (true);
}

void	handle_bump(t_hit_record *rec, t_objects *obj)
{
	if (obj->type == SPHERE)
	{
		if (!sphere_bump(rec, obj->object))
			return ;
	}
	else if (obj->type == PLANE)
	{
		if (!plane_bump(rec, obj->object))
			return ;
	}
	else
		return ;
	normalize(&rec->n_hit);
}

void	textures_binding(t_objects *shapes, t_mrt *img)
{
	t_objects	*shape;

	shape = shapes;
	while (shape)
	{
		if (shape->type != TRIANGLE && shape->type != CONE)
			texture_process(shape->type)(shape, img);
		shape = shape->next;
	}
}
