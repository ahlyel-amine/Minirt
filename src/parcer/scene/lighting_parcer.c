/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_parcer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/07 17:20:14 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parcer.h"
#include "tools.h"
#include "libft.h"
#include "library.h"
#include <stdbool.h>
#include <limits.h>

bool	lighting_parcer(char *line, t_data *data)
{
	bool		success;
	static bool	visited;

	if (visited)
		return (ft_putendl_fd("minirt: error: duplicate of lighting information", 2), false);
	visited = true;
	success = true;
	line += 2;
	data->lighting.ratio =  ft_atod(&line, &success, 1, 0);
	if (!success)
		return (ft_putendl_fd("minirt: invalid ambient lighting value", 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &data->lighting.clr))
		return (false);
	return (true);
}
