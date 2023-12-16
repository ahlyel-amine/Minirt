/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:49:37 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/16 11:41:42 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"

typedef void (*t_texture_clear)(void *);

void	sphere_texutre_c(void *shape)
{
	t_sphere	*s;

	s = (t_sphere *)shape;
	if (s->spec.texture)
		free(s->spec.texture);
	if (s->spec.bump)
		free(s->spec.bump);
}

void	plane_texutre_c(void *shape)
{
	t_plane	*p;

	p = (t_plane *)shape;
	if (p->spec.texture)
		free(p->spec.texture);
	if (p->spec.bump)
		free(p->spec.bump);
}

void	cy_texture_c(void *shape)
{
	t_cylender *c;

	c = (t_cylender *)shape;
	if (c->spec.texture)
		free(c->spec.texture);
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
	int index;

	index = (type == SPHERE) * 1 + (type == PLANE) * 2 + (type == CYLENDER) * 3;
	if (index)
		shapes_texture_clear(index)(shape);
}

void	clearobjs(t_objects **lst)
{
	t_objects	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		clear_texture((*lst)->object, (*lst)->type);
		if ((*lst)->type == CYLENDER)
			clearobjs(&(((t_cylender *)((*lst)->object))->p_face));
		free ((*lst)->object);
		if ((*lst)->t_copy)
			free(((*lst)->t_copy));
		if ((*lst)->b_copy)
			free((*lst)->b_copy);
		free(*lst);
		*lst = tmp;
	}
}
void	clearlights(t_light **lst)
{
	t_light	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

void	get_integer(char **line, int *integer)
{
	int	i;
	
	i = 0;
	*line += skip_spaces(*line);
	while (ft_isdigit((*line)[i]))
		i++;
	*integer = ft_atoi((*line));
	*line += i;
}