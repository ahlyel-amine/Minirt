/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parcer_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/11 17:49:07 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool sphere_parcer(line, data)
char *line;
t_data *data;
{
	t_objects	*object;
	t_sphere	*sphere;

	sphere = ft_calloc(sizeof(t_sphere), 1);
	if (!sphere)
		return (false);
	data->counter.sphere += 1;
	line += 3;
	if (!cordinate_parcer(&line, &sphere->cord, INT_MAX, INT_MIN))
		return (free(sphere), ft_putendl_fd("minirt: sp invalid cordinate format", 2), false);
	if (!ft_atod(&line, &sphere->diameter, INT_MAX, INT_MIN))
		return (free(sphere), ft_putendl_fd("minirt: invalid diameter format", 2), false);
	line += skip_spaces(line);
	int a = color_parcer(line, &sphere->clr);
	if (a == -1)
		return (free(sphere), ft_putendl_fd("minirt: sphere invalid color format", 2), false);
	line += skip_spaces(line + a) + a;
	if (!check_for_features(line, &sphere->spec))
		return (free(sphere), false);
	// ft_atod(&line, &sphere->spec.intensity, INT_MAX, INT_MIN);
	// line += skip_spaces(line);
	// ft_atod(&line, &sphere->spec.shininess_factor, 1, 0);
	// line += skip_spaces(line);
	// ft_atod(&line, &sphere->spec.reflection, 1, 0);
	object = newobject(sphere, SPHERE);
	if (!object)
		return (free(sphere), false);
	addobject_front(&data->objects, object);
	return (true);
}
