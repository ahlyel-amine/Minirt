/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:40:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/10 11:05:55 by aelbrahm         ###   ########.fr       */
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

void color_range_norm(t_vec *color)
{
	if (color->v_x > 1)
		color->v_x = 1.0;
	if (color->v_y > 1.0)
		color->v_y = 1.0;
	if (color->v_z > 1.0)
		color->v_z = 1.0;
	if (color->v_x < 0)
		color->v_x = 0.0;
	if (color->v_y < 0)
		color->v_y = 0.0;
	if (color->v_z < 0)
		color->v_z = 0.0;
}

t_vec	c_color(t_vec f_c, t_vec s_c, double p1, double p2)
{
	t_vec r_color;
	r_color.v_x = f_c.v_x * p1 + s_c.v_x * p2;
	r_color.v_y = f_c.v_y * p1 + s_c.v_y * p2;
	r_color.v_z = f_c.v_z * p1 + s_c.v_z * p2;
	color_range_norm(&r_color);
	return (r_color);
}

void	my_mlx_put(t_mrt *rt, int x, int y, int color)
{
	int	iter;
	
	if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
	{
		iter = (x * rt->bit_per_px / 8) + (y * rt->line_len);
		rt->mlx_add[iter] = color;
		rt->mlx_add[++iter] = (color >> 8) & 0xFF;
		rt->mlx_add[++iter] = (color >> 16) & 0xFF;
	}
	return ;
}

int	get_pixel(t_mrt *rt, int x, int y)
{
	int	iter;
	int	color;

	if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
	{
		iter = (x * rt->bit_per_px / 8) + (y * rt->line_len);
		color = rt->mlx_add[iter];
		color |= rt->mlx_add[++iter] << 8;
		color |= rt->mlx_add[++iter] << 16;
		return (color);
	}
	return (0);
}

int	rgb_to_int(t_coord color)
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

	if (sp)
	{
		x = ((int)((u) * texture->width));
		y = (1 - v) * texture->height;
	}
	else
	{
		x = ((int)((u) * texture->width) + texture->width / 2) % (texture->width);
		y = ((int)((1 - v) * texture->height) + texture->height / 2) % (texture->height);
	}
	index = (x * texture->bpp / 8) + (y * texture->line_len);
	color.v_x = (unsigned char)texture->addr[abs(index) + 2] / 255.0;
	color.v_y = (unsigned char)texture->addr[abs(index) + 1] / 255.0;
	color.v_z = (unsigned char)texture->addr[abs(index)] / 255.0;
	return (color);
}

void	check_color(t_objects *object, t_hit_record *rec)
{
	double u;
	double v;

	if (object)
	{
		if (object->type == SPHERE && ((t_sphere *)(object->object))->spec.texture)
		{
			get_uv_sphere(object->object, rec, &u, &v);
			rec->h_color = get_tex_color(((t_sphere *)(object->object))->texture, u, v, true);
		}
		else if (object->type == CYLENDER && ((t_cylender *)(object->object))->spec.texture)
		{
			get_uv_cylinder((t_cylender *)object->object, rec, &u, &v);
			rec->h_color = get_tex_color(((t_cylender *)(object->object))->texture, u, v, false);
		}
		else if (object->type == PLANE && ((t_plane *)(object->object))->spec.texture)
		{
			get_uv_plane((t_plane *)object->object, rec, &u, &v);
			rec->h_color = get_tex_color(((t_plane *)(object->object))->texture, u, v, false);
		}
	}
}
