/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 05:30:00 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/22 05:47:54 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include <mlx.h>
#include <stdlib.h>

void	*bump_texture(t_sphere *sphere, t_mrt *img)
{
	if (sphere->spec.bump)
	{
		sphere->bump = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!sphere->bump)
			return (free(sphere->spec.bump), sphere->spec.bump = NULL, NULL);
		sphere->bump->path = sphere->spec.bump;
		sphere->bump->img = mlx_xpm_file_to_image(img->mlx, sphere->bump->path, \
		&sphere->bump->width, &sphere->bump->height);
		if (!sphere->bump->img)
			return (free(sphere->spec.bump), sphere->spec.bump = NULL, NULL);
		else
			sphere->bump->addr = mlx_get_data_addr(sphere->bump->img, \
			&sphere->bump->bpp, &sphere->bump->line_len, &sphere->bump->endian);
		return ((void *)(sphere->bump));
	}
	return (NULL);
}

void	*bump_texture_p(t_plane *p, t_mrt *img)
{
	if (p->spec.bump)
	{
		p->bump = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!p->bump)
			return (free(p->spec.bump), p->spec.bump = NULL, NULL);
		p->bump->path = p->spec.bump;
		p->bump->img = mlx_xpm_file_to_image(img->mlx, p->bump->path, \
		&p->bump->width, &p->bump->height);
		if (!p->bump->img)
			return (free(p->spec.bump), p->spec.bump = NULL, NULL);
		else
			p->bump->addr = mlx_get_data_addr(p->bump->img, &p->bump->bpp, \
			&p->bump->line_len, &p->bump->endian);
		return ((void *)(p->bump));
	}
	return (NULL);
}
