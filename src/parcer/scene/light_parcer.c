/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:47 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/07 17:20:11 by aahlyel          ###   ########.fr       */
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
	bool			success;

	if (visited)
		return (ft_putendl_fd("minirt: error: duplicate of light information", 2), false);
	success = true;
	visited = true;
	line += 2;
	if (!cordinate_parcer(&line, &data->light.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: L invalid cordinate format", 2), false);
	data->light.brightness = ft_atod(&line, &success, 1, 0);
	if (!success)
		return (ft_putendl_fd("minirt: invalid brightness format", 2), false);
	/*
	if (this is bonus)
	{
		line += skip_spaces(line);
		if (!color_parcer(line, &data->light.clr))
			return (false);
	}
	else if (this is mandatory)
	{
	*/
	line += skip_spaces(line);
	if (!color_parcer(line, &data->light.clr))
		return (false);
	return (true);
}
