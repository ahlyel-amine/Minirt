/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:47 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/17 02:38:40 by aahlyel          ###   ########.fr       */
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
	// static	bool	visited;
	bool			success;

	// if (visited)
	// 	return (ft_putendl_fd("minirt: error: duplicate of light information", 2), false);
	success = true;
	// visited = true;
	t_light	*light;
	t_light	single_light;

	line += 2;
	if (!cordinate_parcer(&line, &single_light.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: L invalid cordinate format", 2), false);
	single_light.brightness = ft_atod(&line, &success, 1, 0);
	if (!success)
		return (ft_putendl_fd("minirt: invalid brightness format", 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &single_light.clr))
		return (false);
	light = newlight(single_light);
	if (!light)
		return (false);
	addlight(&data->light, light);
	return (true);
}
