/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parcer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/14 20:56:59 by aelbrahm         ###   ########.fr       */
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

bool cone_parcer(char *line, t_data *data)
{
	t_objects	*object;
	t_cone	*cone;

	cone = ft_calloc(sizeof(t_cone), 1);
	if (!cone)
		return (false);
	data->counter.cone += 1;
	line += 3;
	if (!cordinate_parcer(&line, &cone->cord, INT_MAX, INT_MIN))
		return (free(cone), ft_putendl_fd("minirt:  cn invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &cone->normalized, 1, -1))
		return (free(cone), ft_putendl_fd("minirt: invalid normalized format", 2), false);
	if (!ft_atod(&line, &cone->half_angle, 180, 0))
		return (free(cone), ft_putendl_fd("minirt: invalid half angle format", 2), false);
	if (!ft_atod(&line, &cone->height, INT_MAX, INT_MIN))
		return (free(cone), ft_putendl_fd("minirt: invalid height format", 2), false);
	line += skip_spaces(line);
	int a = color_parcer(line, &cone->clr);
	if (a == -1)
		return (free(cone), ft_putendl_fd("minirt: cone invalid color format", 2), false);
	line += skip_spaces(line + a) + a;
	if (!check_for_features(line, &cone->spec))
		return (free(cone), false);
	object = newobject(cone, CONE);
	if (!object)
		return (free(cone), false);
	addobject_front(&data->objects, object);
	return (true);
}
