/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:40:55 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/14 18:30:13 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"
#include "vector.h"
#include "draw.h"
#include "tools.h"
#include "draw.h"

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
