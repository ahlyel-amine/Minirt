/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:40:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/25 17:41:00 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "minirt_bonus.h"
#include "vector_bonus.h"
#include "draw_bonus.h"
#include "tools_bonus.h"
#include "draw_bonus.h"

void	color_range_norm(t_vec *color)
{
	color->v_x = (color->v_x > 1.0) * 1.0 + (color->v_x <= 1.0) * color->v_x;
	color->v_y = (color->v_y > 1.0) * 1.0 + (color->v_y <= 1.0) * color->v_y;
	color->v_z = (color->v_z > 1.0) * 1.0 + (color->v_z <= 1.0) * color->v_z;
	color->v_x = (color->v_x < 0.0) * 0.0 + (color->v_x >= 0.0) * color->v_x;
	color->v_y = (color->v_y < 0.0) * 0.0 + (color->v_y >= 0.0) * color->v_y;
	color->v_z = (color->v_z < 0.0) * 0.0 + (color->v_z >= 0.0) * color->v_z;
}

t_vec	c_color(t_vec f_c, t_vec s_c, double p1, double p2)
{
	t_vec	r_color;

	r_color.v_x = f_c.v_x * p1 + s_c.v_x * p2;
	r_color.v_y = f_c.v_y * p1 + s_c.v_y * p2;
	r_color.v_z = f_c.v_z * p1 + s_c.v_z * p2;
	color_range_norm(&r_color);
	return (r_color);
}

int	rgb_to_int(t_vec color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.0 * (color.v_x));
	g = (int)(255.0 * (color.v_y));
	b = (int)(255.0 * color.v_z);
	return (r << 16 | g << 8 | b);
}

t_vec	get_tex_color(t_texture_img *texture, double u, double v, bool sp)
{
	int		x;
	int		y;
	int		index;
	t_vec	color;

	x = (sp > 0) * ((int)((u) * (texture->width - 1))) + \
	(sp < 1) * ((int)((u) * texture->width)) % (texture->width);
	y = (sp > 0) * ((1 - v) * (texture->height - 1)) + \
	(sp < 1) * (((int)((1 - v) * texture->height)) % (texture->height));
	index = (x * texture->bpp / 8) + (y * texture->line_len);
	color.v_x = (unsigned char)texture->addr[abs(index) + 2] / 255.0;
	color.v_y = (unsigned char)texture->addr[abs(index) + 1] / 255.0;
	color.v_z = (unsigned char)texture->addr[abs(index)] / 255.0;
	return (color);
}

void	check_color(t_objects *object, t_hit_record *rec)
{
	double	u_v[2];

	if (!object)
		return ;
	if (object->type == SPHERE && object->texture)
	{
		get_uv_sphere(object->object, rec, &u_v[0], &u_v[1]);
		rec->h_color = get_tex_color(object->texture, \
		u_v[0], u_v[1], true);
	}
	else if (object->type == CYLENDER && object->texture)
	{
		get_uv_cylinder((t_cylender *)object->object, rec, &u_v[0], &u_v[1]);
		rec->h_color = get_tex_color(object->texture, \
		u_v[0], u_v[1], false);
	}
	else if (object->type == PLANE && object->texture)
	{
		get_uv_plane((t_plane *)object->object, rec, &u_v[0], &u_v[1]);
		rec->h_color = get_tex_color(object->texture, \
		u_v[0], u_v[1], false);
	}
}
