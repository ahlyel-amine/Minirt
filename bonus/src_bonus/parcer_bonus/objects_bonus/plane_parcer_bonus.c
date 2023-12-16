/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parcer_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/16 12:32:35 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer_bonus.h"
#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool	plane_parcer(char *line, t_data *data)
{
	t_plane		plane;
	int			i;

	ft_memset(&plane, 0, sizeof(t_plane));
	data->counter.plane += 1;
	line += 3;
	if (!cordinate_parcer(&line, &plane.cord, INT_MAX, INT_MIN))
		return (ft_print_errors(4, ERR, S_NAME, ERR_PL, ERR_CORD), false);
	if (!cordinate_parcer(&line, &plane.normalized, 1, -1))
		return (ft_print_errors(4, ERR, S_NAME, ERR_CY, ERR_N), false);
	line += skip_spaces(line);
	i = color_parcer(line, &plane.clr);
	if (i == -1)
		return (ft_print_errors(4, ERR, S_NAME, ERR_CY, ERR_COLOR), false);
	line += skip_spaces(line + i) + i;
	if (!check_for_features(line, &plane.spec))
		return (false);
	if (!object_validate(T_PLANE, PLANE, data, &plane))
		return (false);
	return (true);
}
