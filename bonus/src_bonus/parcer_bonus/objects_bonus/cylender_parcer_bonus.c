/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender_parcer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/11 17:50:36 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "vector_bonus.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

static void	calculate_disk_plan(t_cylender *cylinder, t_objects *obj, bool is_top)
{
	t_plane *plan;

	plan = obj->object;
	plan->normalized = cylinder->normalized;
	if (is_top)
		plan->cord = vec_addition(cylinder->cord, scalar_mult(cylinder->normalized, cylinder->height * 0.5));
	else
		plan->cord = vec_sub(cylinder->cord, scalar_mult(cylinder->normalized, cylinder->height * 0.5));
}

bool	cylinder_cap(t_cylender *c)
{
	t_plane	*top;
	t_plane	*bottom;

	top = (t_plane *)ft_calloc(sizeof(t_plane), 1);
	if (!top)
		return (false);
	bottom = (t_plane *)ft_calloc(sizeof(t_plane), 1);
	if (!bottom)
		return (free(top), false);
	c->p_face = newobject(top, PLANE);
	if (!c->p_face)
		return (free(top), free(bottom), false);
	addobject_front(&c->p_face, newobject(bottom, PLANE));
	if (!c->p_face->next)
		return (clearobjs(&c->p_face),false);
	normalize(&c->normalized);
	calculate_disk_plan(c, c->p_face, true);
	calculate_disk_plan(c, c->p_face->next, false);
	return (true);
}

bool cylender_parcer(char *line, t_data *data)
{
	t_objects	*object;
	t_cylender	*cylender;

	cylender = ft_calloc(sizeof(t_cylender), 1);
	if (!cylender)
		return (false);
	data->counter.cylender += 1;
	line += 3;
	if (!cordinate_parcer(&line, &cylender->cord, INT_MAX, INT_MIN))
		return (free(cylender), ft_putendl_fd("minirt:  cy invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &cylender->normalized, 1, -1))
		return (free(cylender), ft_putendl_fd("minirt: invalid normalized format", 2), false);
	if (!ft_atod(&line, &cylender->diameter, INT_MAX, INT_MIN))
		return (free(cylender), ft_putendl_fd("minirt: invalid diameter format", 2), false);
	if (!ft_atod(&line, &cylender->height, INT_MAX, INT_MIN))
		return (free(cylender), ft_putendl_fd("minirt: invalid diameter format", 2), false);
	line += skip_spaces(line);
	int a = color_parcer(line, &cylender->clr);
	if (a == -1)
		return (free(cylender), ft_putendl_fd("minirt: cylender invalid color format", 2), false);
	line += skip_spaces(line + a) + a;
	if (!check_for_features(line, &cylender->spec))
		return (free(cylender), false);
	// ft_atod(&line, &cylender->spec.intensity, INT_MAX, INT_MIN);
	// line += skip_spaces(line);
	// ft_atod(&line, &cylender->spec.shininess_factor, 1, 0);
	// line += skip_spaces(line);
	// ft_atod(&line, &cylender->spec.reflection, 1, 0);
	object = newobject(cylender, CYLENDER);
	if (!object)
		return (free(cylender), false);
	addobject_front(&data->objects, object);
	return (cylinder_cap(cylender));
}
