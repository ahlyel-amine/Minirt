/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_parcer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/17 21:31:18 by aahlyel          ###   ########.fr       */
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

	if (!data && !line)
		return (visited);
	if (visited)
		return (print_err(4, ERR, NAME, ERR_A, ERR_DUP), false);
	visited = true;
	line += 2;
	if (!ft_atod(&line, &data->lighting.ratio, 1, 0))
		return (print_err(5, ERR, NAME, ERR_A, ERR_V, "\n"), false);
	line += skip_spaces(line);
	if (color_parcer(line, &data->lighting.clr) == -1)
		return (print_err(4, ERR, NAME, ERR_A, ERR_COLOR), false);
	return (true);
}
