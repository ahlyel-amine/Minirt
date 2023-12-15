/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:10:59 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/15 16:29:05 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"
#include <mlx.h>
#include <stdlib.h>

void	*bump_texture_2(t_plane *p, t_mrt *img)
{
	if (p->spec.bump)
	{
		p->bump = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!p->bump)
			return (free(p->spec.bump), NULL);
		p->bump->path = p->spec.bump;
		p->bump->img = mlx_xpm_file_to_image(img->mlx, p->bump->path, &p->bump->width, &p->bump->height);
		if (!p->bump->img)
			return (free(p->spec.bump), p->spec.bump = NULL, p->bump->img = NULL, NULL);
		else
			p->bump->addr = mlx_get_data_addr(p->bump->img, &p->bump->bpp, &p->bump->line_len, &p->bump->endian);
		return ((void *)(p->bump));
	}
	return (NULL);
}
static bool	texture_plane(void *p, t_mrt *img)
{
	t_plane	*plane;

	plane = (t_plane *)p;
	if (plane->spec.texture)
	{
		plane->texture = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!plane->texture)
			return (false);
		plane->texture->path = plane->spec.texture;
		plane->texture->img = mlx_xpm_file_to_image(img->mlx, plane->texture->path, &plane->texture->width, &plane->texture->height);
		if (!plane->texture->img)
			return (free(plane->spec.texture), plane->spec.texture = NULL, plane->texture->img = NULL, false);
		else
			plane->texture->addr = mlx_get_data_addr(plane->texture->img, &plane->texture->bpp, &plane->texture->line_len, &plane->texture->endian);
	}
	bump_texture_2(plane, img);
	return (true);
}
void	*bump_texture(t_sphere *sphere, t_mrt *img)
{
	if (sphere->spec.bump)
	{
		sphere->bump = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!sphere->bump)
			return (free(sphere->spec.bump), sphere->spec.bump = NULL, NULL);
		sphere->bump->path = sphere->spec.bump;
		sphere->bump->img = mlx_xpm_file_to_image(img->mlx, sphere->bump->path, &sphere->bump->width, &sphere->bump->height);
		if (!sphere->bump->img)
			return (free(sphere->spec.bump), sphere->spec.bump = NULL, NULL);
		else
			sphere->bump->addr = mlx_get_data_addr(sphere->bump->img, &sphere->bump->bpp, &sphere->bump->line_len, &sphere->bump->endian);
		return ((void *)(sphere->bump));
	}
	return (NULL);
}
static bool	texture_sphere(void *sphere, t_mrt *img)
{
	t_sphere	*s;

	s = (t_sphere *)sphere;
	if (s->spec.texture)
	{
		s->texture = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!s->texture)
			return (free(s->spec.texture), s->spec.texture = NULL, false);
		s->texture->path = s->spec.texture;
		s->texture->img = mlx_xpm_file_to_image(img->mlx, s->texture->path, &s->texture->width, &s->texture->height);
		if (!s->texture->img)
			return (free(s->spec.texture), s->spec.texture = NULL, false);
		else
			s->texture->addr = mlx_get_data_addr(s->texture->img, &s->texture->bpp, &s->texture->line_len, &s->texture->endian);
	}
	bump_texture(s, img);
	return (true);
}

static bool	texture_cylinder(void *cylinder, t_mrt *img)
{
	t_cylender	*c;

	c = (t_cylender *)cylinder;
	if (c->spec.texture)
	{
		c->texture = (t_texture_img *)malloc(sizeof(t_texture_img));
		if (!c->texture)
			return (false);
		c->texture->path = c->spec.texture;
		c->texture->img = mlx_xpm_file_to_image(img->mlx, c->texture->path, &c->texture->width, &c->texture->height);
		if (!c->texture->img)
			return (free(c->spec.texture), c->spec.texture = NULL, false);
		else
			c->texture->addr = mlx_get_data_addr(c->texture->img, &c->texture->bpp, &c->texture->line_len, &c->texture->endian);
	}
	return (true);
}

texture texture_process(int type)
{
	texture func[3];
	func[SPHERE] = texture_sphere;
	func[PLANE] = texture_plane;
	func[CYLENDER] = texture_cylinder;
	return (func[type]);
}

void	textures_binding(t_objects *shapes, t_mrt *img)
{
	t_objects	*shape;

	shape = shapes;
	while (shape)
	{
		if (shape->type != TRIANGLE && shape->type != CONE)
			texture_process(shape->type)(shape->object, img);
		shape = shape->next;
	}
}

