/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:42:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/19 20:03:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"

void	sphere_texutre_c(void *shape)
{
	t_sphere	*s;

	s = (t_sphere *)shape;
	if (s->spec.texture)
	{
		free(s->spec.texture);
		free(s->texture);
	}
	if (s->spec.bump)
	{
		free(s->spec.bump);
		free(s->bump);
	}
}

void	plane_texutre_c(void *shape)
{
	t_plane	*p;

	p = (t_plane *)shape;
	if (p->spec.texture)
	{
		free(p->spec.texture);
		free(p->texture);
	}
	if (p->spec.bump)
	{
		free(p->spec.bump);
		free(p->bump);
	}
}

void	cy_texture_c(void *shape)
{
	t_cylender	*c;

	c = (t_cylender *)shape;
	if (c->spec.texture)
	{
		free(c->spec.texture);
		free(c->texture);
	}
	if (c->spec.bump)
		free(c->spec.bump);
}

t_texture_clear	shapes_texture_clear(int index)
{
	t_texture_clear	clear[4];

	*(clear) = NULL;
	*(clear + 1) = sphere_texutre_c;
	*(clear + 2) = plane_texutre_c;
	*(clear + 3) = cy_texture_c;
	return (*(clear + index));
}

void	clear_texture(void *shape, int type)
{
	int	index;

	index = (type == SPHERE) * 1 + (type == PLANE) * 2 + (type == CYLENDER) * 3;
	if (index)
		shapes_texture_clear(index)(shape);
}
