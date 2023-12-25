/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 05:30:00 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/25 17:47:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>
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

t_features	*get_specular_add(t_objects *obj)
{
	if (obj->type == PLANE)
		return (&(((t_plane *)obj->object)->spec));
	else if (obj->type == SPHERE)
		return (&(((t_sphere *)obj->object)->spec));
	else if (obj->type == CYLENDER)
		return (&(((t_cylender *)obj->object)->spec));
	return (NULL);
}

bool	bump_texture(t_objects *shape, t_mrt *img)
{
	t_features	*spec;

	spec = get_specular_add(shape);
	if (spec && spec->bump)
	{
		shape->bump = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!shape->bump)
			return (free(spec->bump), spec->bump = NULL, false);
		shape->bump->path = spec->bump;
		shape->bump->img = mlx_xpm_file_to_image(img->mlx, shape->bump->path, \
		&shape->bump->width, &shape->bump->height);
		if (!shape->bump->img)
			return (free(spec->bump), spec->bump = NULL, \
			free(shape->bump), shape->bump = NULL, false);
		else
			shape->bump->addr = mlx_get_data_addr(shape->bump->img, \
			&shape->bump->bpp, &shape->bump->line_len, &shape->bump->endian);
		return (true);
	}
	return (false);
}
