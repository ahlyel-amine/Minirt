/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:10:59 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/22 05:40:19 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>
#include <stdlib.h>

static bool	texture_plane(void *p, t_mrt *img)
{
	t_plane	*plane;

	plane = (t_plane *)(((t_objects *)p)->object);
	if (plane->spec.texture)
	{
		plane->texture = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!plane->texture)
			return (false);
		plane->texture->path = plane->spec.texture;
		plane->texture->img = mlx_xpm_file_to_image(img->mlx, \
		plane->texture->path, &plane->texture->width, &plane->texture->height);
		if (!plane->texture->img)
			return (free(plane->spec.texture), \
			plane->spec.texture = NULL, false);
		else
			plane->texture->addr = mlx_get_data_addr(plane->texture->img, \
			&plane->texture->bpp, &plane->texture->line_len, \
			&plane->texture->endian);
	}
	bump_texture_p(plane, img);
	return (true);
}

static bool	texture_sphere(void *sphere, t_mrt *img)
{
	t_sphere	*s;

	s = (t_sphere *)(((t_objects *)sphere)->object);
	if (s->spec.texture)
	{
		s->texture = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!s->texture)
			return (free(s->spec.texture), s->spec.texture = NULL, false);
		s->texture->path = s->spec.texture;
		s->texture->img = mlx_xpm_file_to_image(img->mlx, s->texture->path, \
		&s->texture->width, &s->texture->height);
		if (!s->texture->img)
			return (free(s->spec.texture), s->spec.texture = NULL, false);
		else
			s->texture->addr = mlx_get_data_addr(s->texture->img, \
			&s->texture->bpp, &s->texture->line_len, &s->texture->endian);
	}
	bump_texture(s, img);
	return (true);
}

static bool	texture_cylinder(void *cylinder, t_mrt *img)
{
	t_cylender	*c;

	c = (t_cylender *)(((t_objects *)cylinder)->object);
	if (c->spec.texture)
	{
		c->texture = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!c->texture)
			return (free(c->spec.texture), c->spec.texture = NULL, false);
		c->texture->path = c->spec.texture;
		c->texture->img = mlx_xpm_file_to_image(img->mlx, c->texture->path, \
		&c->texture->width, &c->texture->height);
		if (!c->texture->img)
			return (free(c->spec.texture), c->spec.texture = NULL, false);
		else
			c->texture->addr = mlx_get_data_addr(c->texture->img, \
			&c->texture->bpp, &c->texture->line_len, &c->texture->endian);
	}
	return (true);
}

t_texture	texture_process(int type)
{
	static t_texture	func[3];
	static bool			init;

	if (!init)
	{
		init = true;
		func[SPHERE] = texture_sphere;
		func[PLANE] = texture_plane;
		func[CYLENDER] = texture_cylinder;
	}
	return (func[type]);
}
