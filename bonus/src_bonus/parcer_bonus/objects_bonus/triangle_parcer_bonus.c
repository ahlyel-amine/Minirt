/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_parcer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:59:13 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/18 16:18:03 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool	triangle_parcer(char *line, t_data *data)
{
	t_triangle	triangle;
	int			i;

	ft_memset(&triangle, 0, sizeof(t_triangle));
	data->counter.triangle += 1;
	line += 3;
	if (!cordinate_parcer(&line, &triangle.cord1, INT_MAX, INT_MIN))
		return (print_err(4, ERR, NAME, ERR_TR, ERR_CORD), false);
	if (!cordinate_parcer(&line, &triangle.cord2, INT_MAX, INT_MIN))
		return (print_err(4, ERR, NAME, ERR_TR, ERR_CORD), false);
	if (!cordinate_parcer(&line, &triangle.cord3, INT_MAX, INT_MIN))
		return (print_err(4, ERR, NAME, ERR_TR, ERR_CORD), false);
	line += skip_spaces(line);
	i = color_parcer(line, &triangle.clr);
	if (i == -1)
		return (print_err(4, ERR, NAME, ERR_TR, ERR_COLOR), false);
	line += skip_spaces(line + i) + i;
	if (!check_for_features(line, &triangle.spec))
		return (false);
	if (!object_validate(T_TRIANGLE, TRIANGLE, data, &triangle))
		return (false);
	return (true);
}
