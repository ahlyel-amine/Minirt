/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_binding_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 03:17:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/24 10:15:09 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library_bonus.h"
#include "vector_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>
#include <stdlib.h>

bool	texture_init(t_objects *shape, t_mrt *img)
{
	t_specular_light	*spc;

	spc = get_specular_add(shape);
	if (spc && spc->texture)
	{
		shape->texture = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!shape->texture)
			return (free(spc->texture), spc->texture = NULL, false);
		shape->texture->path = spc->texture;
		shape->texture->img = mlx_xpm_file_to_image(img->mlx, \
		shape->texture->path, &shape->texture->width, &shape->texture->height);
		if (!shape->texture->img)
			return (free(spc->texture), spc->texture = NULL, \
			free(shape->texture), shape->texture = NULL, false);
		else
			shape->texture->addr = mlx_get_data_addr(shape->texture->img, \
			&shape->texture->bpp, &shape->texture->line_len, \
			&shape->texture->endian);
		if (shape->type == SPHERE || shape->type == PLANE)
			shape->features.bump = bump_texture(shape, img);
		return (true);
	}
	return (false);
}

bool	sphere_bump(t_hit_record *rec, t_objects *shape)
{
	t_vec		perp_u;
	t_vec		perp_v;
	t_bump_data	b;

	get_uv_sphere((t_sphere *)(shape->object), rec, &b.u, &b.v);
	b.axis = (t_vec){0, 0, 1};
	b.x = ((int)(b.u * (shape->bump->width - 1)));
	b.y = (((1 - b.v) * (shape->bump->height - 1)));
	b.u = get_cscale_texture(shape->bump, b.x, b.y);
	b.v = get_cscale_texture(shape->bump, (b.x + 1) % \
	(shape->bump->width - 1), b.y);
	b.b_scale_u = (b.u - b.v) * -0.2;
	b.v = get_cscale_texture(shape->bump, b.x, (b.y + 1) % \
	(shape->bump->height - 1));
	b.b_scale_v = (b.u - b.v) * -0.2;
	perp_u = cross_product(rec->n_hit, b.axis);
	perp_v = cross_product(rec->n_hit, perp_u);
	rec->n_hit = vec_addition(rec->n_hit, \
	scalar_mult(perp_u, b.b_scale_v));
	rec->n_hit = vec_addition(rec->n_hit, \
	scalar_mult(perp_v, b.b_scale_u));
	return (true);
}

bool	plane_bump(t_hit_record *rec, t_objects *shape)
{
	t_vec		perp_u;
	t_vec		perp_v;
	t_bump_data	b;

	get_uv_plane((t_plane *)(shape->object), rec, &b.u, &b.v);
	b.axis = normalized(((t_plane *)(shape->object))->normalized);
	b.x = ((int)(b.u * (shape->bump->width - 1)) % shape->bump->width);
	b.y = (int)((1 - b.v) * (shape->bump->height - 1)) % shape->bump->height;
	b.u = get_cscale_texture(shape->bump, b.x, b.y);
	b.v = get_cscale_texture(shape->bump, \
	(b.x + 1) % shape->bump->width, b.y);
	b.b_scale_u = (b.u - b.v) * -0.05;
	b.v = get_cscale_texture(shape->bump, \
	b.x, (b.y + 1) % shape->bump->height);
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
	if (!obj)
		return ;
	if (obj->type == SPHERE && obj->bump)
	{
		if (!sphere_bump(rec, obj))
			return ;
	}
	else if (obj->type == PLANE && obj->bump)
	{
		if (!plane_bump(rec, obj))
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
			shape->features.texture = texture_init(shape, img);
		shape = shape->next;
	}
}
