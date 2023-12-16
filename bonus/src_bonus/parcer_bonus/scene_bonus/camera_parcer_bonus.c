/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parcer_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/16 14:32:01 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool	camera_parcer(char *line, t_data *data)
{
	static bool	visited;
	int			i;

	if (!data && !line)
		return (visited);
	if (visited)
		return (ft_print_errors(4, ERR, S_NAME, ERR_C, ERR_DUP), false);
	visited = true;
	line += 2;
	if (!cordinate_parcer(&line, &data->camera.cord, INT_MAX, INT_MIN))
		return (ft_print_errors(4, ERR, S_NAME, ERR_C, ERR_CORD), false);
	if (!cordinate_parcer(&line, &data->camera.normalized, 1, -1))
		return (ft_print_errors(4, ERR, S_NAME, ERR_C, ERR_N), false);
	line += skip_spaces(line);
	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[skip_spaces(line + i) + i])
		return (ft_print_errors(5, ERR, S_NAME, ERR_C, ERR_V, ERR_VF), false);
	data->camera.v_field = (unsigned char)ft_atoi(line);
	return (true);
}
