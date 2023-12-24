/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 05:30:00 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/24 01:26:31 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>
#include <stdlib.h>

t_specular_light	*get_specular_add(t_objects *obj)
{
	if (obj->type == PLANE)
		return (&(((t_plane *)obj->object)->spec));
	else if (obj->type == SPHERE)
		return (&(((t_sphere *)obj->object)->spec));
	else if (obj->type == CYLENDER)
		return (&(((t_cylender *)obj->object)->spec));
	return (NULL);
}

void	*bump_texture(t_objects *shape, t_mrt *img)
{
	t_specular_light	*spec;

	spec = get_specular_add(shape);
	if (spec && spec->bump)
	{
		shape->bump = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!shape->bump)
			return (free(spec->bump), spec->bump = NULL, NULL);
		shape->bump->path = spec->bump;
		shape->bump->img = mlx_xpm_file_to_image(img->mlx, shape->bump->path, \
		&shape->bump->width, &shape->bump->height);
		if (!shape->bump->img)
			return (free(spec->bump), spec->bump = NULL,\
			free(shape->bump), shape->bump = NULL, NULL);
		else
			shape->bump->addr = mlx_get_data_addr(shape->bump->img, \
			&shape->bump->bpp, &shape->bump->line_len, &shape->bump->endian);
		return ((void *)(shape->bump));
	}
	return (NULL);
}
