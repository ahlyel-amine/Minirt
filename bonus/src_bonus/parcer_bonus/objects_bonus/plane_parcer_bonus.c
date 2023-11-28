/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 11:47:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer_bonus.h"
#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool plane_parcer(char *line, t_data *data)
{
	t_objects	*object;
	t_plane		*plane;

	plane = ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		return (false);
	data->counter.plane += 1;
	line += 3;
	if (!cordinate_parcer(&line, &plane->cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: pl invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &plane->normalized, 1, -1))
		return (ft_putendl_fd("minirt: invalid normalized format", 2), false);
	line += skip_spaces(line);
	int a = color_parcer(line, &plane->clr);
	if (a == -1)
		return (ft_putendl_fd("minirt: plane invalid color format", 2), false);
	line += skip_spaces(line + a) + a;
	ft_atod(&line, &plane->spec.intensity, INT_MAX, INT_MIN);
	line += skip_spaces(line);
	ft_atod(&line, &plane->spec.shininess_factor, 1, 0);
	line += skip_spaces(line);
	ft_atod(&line, &plane->spec.reflection, 1, 0);
	object = newobject(plane, PLANE);
	if (!object)
		return (false);  
	addobject_front(&data->objects, object);
	return (true);
}
