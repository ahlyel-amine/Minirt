/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_parcer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/11 17:49:49 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool	lighting_parcer(char *line, t_data *data)
{
	static bool	visited;

	if (visited)
		return (ft_putendl_fd("minirt: error: duplicate of lighting information", 2), false);
	visited = true;
	line += 2;
	if (!ft_atod(&line, &data->lighting.ratio, 1, 0))
		return (ft_putendl_fd("minirt: invalid ambient lighting value", 2), false);
	line += skip_spaces(line);
	if (color_parcer(line, &data->lighting.clr) == -1)
		return (ft_putendl_fd("minirt: lighting invalid color format", 2), false);
	return (true);
}
