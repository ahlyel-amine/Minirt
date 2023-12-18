/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_parcer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/18 15:55:59 by aelbrahm         ###   ########.fr       */
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
	static bool	visited;

	if (!line && !data)
		return (visited);
	if (visited)
		return (ft_putendl_fd(ERR_A_DUP, 2), false);
	visited = true;
	line += 2;
	if (!ft_atod(&line, &data->lighting.ratio, 1, 0))
		return (ft_putendl_fd(ERR_A_VL, 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &data->lighting.clr))
		return (ft_putendl_fd(ERR_A_COLOR, 2), false);
	return (true);
}
