/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:47 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/03 22:29:04 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parcer.h"
#include "tools.h"
#include "libft.h"
#include "library.h"
#include <stdbool.h>
#include <limits.h>

bool light_parcer(char *line, t_data *data)
{
	static	bool	visited;
	t_light			*light;
	t_objects		*object;
	bool			success;

	if (visited)
		return (ft_putendl_fd("minirt: error: duplicate of light information", 2), false);
	success = true;
	visited = true;
	light = ft_calloc(sizeof(t_light), 1);
	if (!light)
		return (false);
	line += 2;
	if (!cordinate_parcer(&line, &light->cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: invalid cordinate format", 2), false);
	light->brightness = ft_atod(&line, &success, 1, 0);
	if (!success)
		return (ft_putendl_fd("minirt: invalid brightness format", 2), false);
	/*
	if (this is bonus)
	{
		line += skip_spaces(line);
		if (!color_parcer(line, &light->clr))
			return (false);
	}
	else if (this is mandatory)
	{
	*/
	if (line[skip_spaces(line)])
		return (ft_putendl_fd("minirt: to much arguments", 2), false);
	/*
	}
	*/
	object = newobject(light, LIGHT);
	if (!object)
		return (false);
	addobject_front(&data->objects, object);
	return (true);
}
