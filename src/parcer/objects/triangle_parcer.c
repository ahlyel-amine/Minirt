/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_parcer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:59:13 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/24 09:09:57 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"
#include "structs.h"
#include "tools.h"
#include "libft.h"
#include "library.h"
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
	if (!color_parcer(line, &triangle->clr))
		return (ft_putendl_fd("minirt: tr invalid color format", 2), false);
	object = newobject(triangle, TRIANGLE);
	if (!object)
		return (false);
	addobject_back(&data->objects, object);
	return (true);
}