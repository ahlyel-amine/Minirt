/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:47 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/18 17:33:51 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parcer.h"
#include "tools.h"
#include "libft.h"
#include "library.h"
#include <stdbool.h>
#include <limits.h>

bool	light_parcer(char *line, t_data *data)
{
	static bool	visited;

	if (!line && !data)
		return (visited);
	if (visited)
		return (ft_putendl_fd(ERR_L_DUP, 2), false);
	visited = true;
	line += 2;
	if (!cordinate_parcer(&line, &data->light.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd(ERR_L_CORD, 2), false);
	if (!ft_atod(&line, &data->light.brightness, 1, 0))
		return (ft_putendl_fd(ERR_L_BR, 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &data->light.clr))
		return (ft_putendl_fd(ERR_L_COLOR, 2), false);
	return (true);
}
