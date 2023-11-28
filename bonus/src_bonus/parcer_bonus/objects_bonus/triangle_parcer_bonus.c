/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_parcer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:59:13 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/28 11:47:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool	triangle_parcer(char *line, t_data *data)
{
	t_objects	*object;
	t_triangle	*triangle;

	triangle = ft_calloc(sizeof(t_triangle), 1);
	if (!triangle)
		return (false);
	data->counter.triangle += 1;
	line += 3;
	if (!cordinate_parcer(&line, &triangle->cord1, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt:  tr invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &triangle->cord2, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt:  tr invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &triangle->cord3, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt:  tr invalid cordinate format", 2), false);
	line += skip_spaces(line);
	int a = color_parcer(line, &triangle->clr);
	if (a == -1)
		return (ft_putendl_fd("minirt: triangle invalid color format", 2), false);
	line += skip_spaces(line + a) + a;
	ft_atod(&line, &triangle->spec.intensity, INT_MAX, INT_MIN);
	line += skip_spaces(line);
	ft_atod(&line, &triangle->spec.shininess_factor, 1, 0);
	line += skip_spaces(line);
	ft_atod(&line, &triangle->spec.reflection, 1, 0);
	object = newobject(triangle, TRIANGLE);
	if (!object)
		return (false);
	addobject_back(&data->objects, object);
	return (true);
}