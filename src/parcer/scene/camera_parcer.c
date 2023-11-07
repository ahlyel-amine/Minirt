/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parcer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/07 17:20:08 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parcer.h"
#include "tools.h"
#include "libft.h"
#include "library.h"
#include <stdbool.h>
#include <limits.h>

bool	camera_parcer(char *line, t_data *data)
{
	static	bool	visited;
	bool			success;
	
	if (visited)
		return (ft_putendl_fd("minirt: error: duplicate of camera information", 2), false);
	success = true;
	visited = true;
	line += 2;
	if (!cordinate_parcer(&line, &data->camera.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: C invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &data->camera.normalized, 1, -1))
		return (ft_putendl_fd("minirt: C n invalid cordinate format", 2), false);
	line += skip_spaces(line);
	int i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[skip_spaces(line + i) + i])
		return (ft_putendl_fd("minirt: invalid v_field format", 2), false);
	data->camera.v_field = (unsigned char)ft_atoi(line);
	return (true);
}
