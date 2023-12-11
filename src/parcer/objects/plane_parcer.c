/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/11 17:43:36 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"
#include "structs.h"
#include "libft.h"
#include "library.h"
#include "tools.h"
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
		return (free(plane), ft_putendl_fd("minirt: pl invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &plane->normalized, 1, -1))
		return (free(plane), ft_putendl_fd("minirt: invalid normalized format", 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &plane->clr))
		return (free(plane), ft_putendl_fd("minirt: plane invalid color format", 2), false);
	object = newobject(plane, PLANE);
	if (!object)
		return (free(plane), false);  
	addobject_front(&data->objects, object);
	return (true);
}
