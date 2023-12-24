/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/18 15:56:54 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"
#include "structs.h"
#include "libft.h"
#include "library.h"
#include "tools.h"
#include <stdbool.h>
#include <limits.h>

bool	plane_parcer(char *line, t_data *data)
{
	t_plane		plane;

	ft_memset(&plane, 0, sizeof(t_plane));
	data->counter.plane += 1;
	line += 3;
	if (!cordinate_parcer(&line, &plane.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd(ERR_PL_CORD, 2), false);
	if (!cordinate_parcer(&line, &plane.normalized, 1, -1))
		return (ft_putendl_fd(ERR_PL_N, 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &plane.clr))
		return (ft_putendl_fd(ERR_PL_COLOR, 2), false);
	if (!object_validate(T_PLANE, PLANE, data, &plane))
		return (false);
	return (true);
}
