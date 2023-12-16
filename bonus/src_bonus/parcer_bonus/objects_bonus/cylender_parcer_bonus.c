/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender_parcer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/16 00:09:46 by aahlyel          ###   ########.fr       */
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

void	calculate_disk_plan(t_cylender *cylinder, t_objects *obj, bool is_top)
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
	t_cylender	cylender;
	int			i;

	ft_memset(&cylender, 0, sizeof(t_cylender));
	data->counter.cylender += 1;
	line += 3;
	if (!cordinate_parcer(&line, &cylender.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd_arg(5, ERR, ERR_CY, ERR 2), false);
	if (!cordinate_parcer(&line, &cylender.normalized, 1, -1))
		return (ft_putendl_fd_arg(5, ERR, ERR_CY, ERR), false);
	if (!ft_atod(&line, &cylender.diameter, INT_MAX, INT_MIN))
		return (ft_putendl_fd_arg(5, ERR, ERR_CY, ERR), false);
	if (!ft_atod(&line, &cylender.height, INT_MAX, INT_MIN))
		return (ft_putendl_fd_arg(5, ERR, ERR_CY, ERR), false);
	line += skip_spaces(line);
	i = color_parcer(line, &cylender.clr);
	if (i == -1)
		return (ft_putendl_fd_arg(5, ERR, ERR_CY, ERR 2), false);
	line += skip_spaces(line + i) + i;
	if (!check_for_features(line, &cylender.spec))
		return (false);
	object_validate(T_CYLENDER, CYLENDER, data, &cylender);
	printf("ooo : %p\n\n\n\n\n", ((t_cylender *)data->objects->object)->texture);
	return (cylinder_cap(data->objects->object));
}
