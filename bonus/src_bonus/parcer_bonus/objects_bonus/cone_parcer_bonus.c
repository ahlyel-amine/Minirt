/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parcer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/24 16:03:28 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "vector_bonus.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool	cone_parcer(char *line, t_data *data)
{
	t_cone	cone;
	int		i;

	data->counter.cone += 1;
	line += 3;
	ft_memset(&cone, 0, sizeof(t_cone));
	if (!cordinate_parcer(&line, &cone.cord, INT_MAX, INT_MIN))
		return (print_err(4, ERR, NAME, ERR_CN, ERR_CORD), false);
	if (!cordinate_parcer(&line, &cone.normalized, 1, -1))
		return (print_err(4, ERR, NAME, ERR_CN, ERR_N), false);
	if (!ft_atod(&line, &cone.half_angle, 180, 0))
		return (print_err(5, ERR, NAME, ERR_CN, ERR_V, ERR_HA), false);
	if (!ft_atod(&line, &cone.height, INT_MAX, INT_MIN))
		return (print_err(5, ERR, NAME, ERR_CN, ERR_V, ERR_HT), false);
	line += skip_spaces(line);
	i = color_parcer(line, &cone.clr);
	if (i == -1)
		return (print_err(4, ERR, NAME, ERR_CN, ERR_COLOR), false);
	line += skip_spaces(line + i) + i;
	if (!features_parcer(line, &cone.spec, CONE))
		return (false);
	if (!object_validate(T_CONE, CONE, data, &cone))
		return (false);
	return (true);
}
