/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parcer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/05 01:38:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parcer.h"
#include "tools.h"
#include "libft.h"
#include "library.h"
#include <stdbool.h>
#include <limits.h>

bool sphere_parcer(line, data)
char *line;
t_data *data;
{
	t_objects	*object;
	t_sphere	*sphere;
	bool		success;

	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (!sphere)
		return (false);
	success = true;
	line += 3;
	printf("%s\n", line);
	if (!cordinate_parcer(&line, &sphere->cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: sp invalid cordinate format", 2), false);
	sphere->diameter = ft_atod(&line, &success, INT_MAX, INT_MIN);
	if (!success)
		return (ft_putendl_fd("minirt: invalid diameter format", 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &sphere->clr))
		return (false);
	object = newobject(sphere, SPHERE);
	if (!object)
		return (false);
	addobject_front(&data->objects, object);
	return (true);
}
