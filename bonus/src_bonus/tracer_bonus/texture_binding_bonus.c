/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_binding_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 03:17:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/11 04:07:12 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library_bonus.h"
#include "vector_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include <stdlib.h>

double get_greyscale_texture_c(t_texture_img *bump, int x, int y)
{
	int		index;
	double	grey;
	t_vec	color;

	index = (x * bump->bpp / 8) + (y * bump->line_len);
	color.v_x = (unsigned char)bump->addr[abs(index) + 2] / 255.0;
	color.v_y = (unsigned char)bump->addr[abs(index) + 1] / 255.0;
	color.v_z = (unsigned char)bump->addr[abs(index)] / 255.0;
	grey = color.v_x + color.v_y * 256.0 + color.v_z * 65536.0;
	return (grey);
}

bool	sphere_bump(t_hit_record *rec, t_sphere *sphere, t_bump_data *b)
{
	if (!sphere->bump)
		return (false);
	get_uv_sphere(sphere, rec, &b->u, &b->v);
	b->axis = (t_vec){0, 1, 0};
	b->x = ((int)(b->u * (sphere->bump->width - 1)));
	b->y = ((1 - b->v) * (sphere->bump->height - 1));
	b->u = get_greyscale_texture_c(sphere->bump, b->x, b->y);
	b->v = get_greyscale_texture_c(sphere->bump, (b->x + 1) % sphere->bump->width, b->y);
	b->b_scale_u = (b->u - b->v);
	b->v = get_greyscale_texture_c(sphere->bump, b->x, (b->y + 1) % sphere->bump->height);
	b->b_scale_v = (b->u - b->v);
	return (true);
}

bool	plane_bump(t_hit_record *rec, t_plane *plane, t_bump_data *b)
{
	if (!plane->bump)
		return (false);
	get_uv_plane(plane, rec, &b->u, &b->v);
	b->axis = plane->normalized;
	b->x = ((int)(b->u * (plane->bump->width - 1)));
	b->y = ((1 - b->v) * (plane->bump->height - 1));
	b->u = get_greyscale_texture_c(plane->bump, b->x, b->y);
	b->v = get_greyscale_texture_c(plane->bump, (b->x + 1) % plane->bump->width, b->y);
	b->b_scale_u = (b->u - b->v);
	b->v = get_greyscale_texture_c(plane->bump, b->x, (b->y + 1) % plane->bump->height);
	b->b_scale_v = (b->u - b->v);
	return (true);
}

void	handle_bump(t_hit_record *rec, t_objects *obj)
{
	t_vec	perp_v;
	t_vec	perp_u;
	t_bump_data b;
	if (obj->type == SPHERE)
	{	if (!sphere_bump(rec, obj->object, &b))
			return ;}
	else if (obj->type == PLANE)
	{	if (!plane_bump(rec, obj->object, &b))
			return ;}
	else
		return ;
	perp_u = cross_product(rec->nHit, b.axis);
	perp_v = cross_product(rec->nHit, perp_u);
	rec->nHit = vec_addition(rec->nHit, scalar_mult(perp_u, b.b_scale_v));
	rec->nHit = vec_addition(rec->nHit, scalar_mult(perp_v, b.b_scale_u));
	normalize(&rec->nHit);
}