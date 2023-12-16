/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_parcer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:59:13 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/15 23:25:43 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer_bonus.h"
#include "structs_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

// bool	check_reflection(line, reflection)
// char **line;
// double *reflection;
// {
// 	*line += skip_spaces(*line);
// 	if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, "r=", 2))
// 	{
// 		*line += 2;
// 		if (!ft_atod(line, reflection, 1, 0))
// 			return (ft_putendl_fd("minirt: invalid reflection", 2), false);
// 	}
// 	*line += skip_spaces(*line);
// 	return (true);
// }

// bool	check_specular(line, specular)
// char **line;
// t_specular_light	*specular;
// {
// 	*line += skip_spaces(*line);
// 	if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, "s=", 2))
// 	{
// 		*line += 2;
// 		if (!ft_atod(line, &specular->intensity, 1, 0))
// 			return (ft_putendl_fd("minirt: invalid specular intensity", 2), false);
// 		(*line)++;
// 		if (!ft_atod(line, &specular->shininess_factor, 1, 0))
// 			return (ft_putendl_fd("minirt: invalid specular shininess factor", 2), false);
// 	}
// 	*line += skip_spaces(*line);
// 	return (true);
// }

// bool	check_for_features(line, triangle)
// char *line;
// t_triangle *triangle;
// {
// 	while (line)
// 	{
// 		if (!check_reflection(&line, &triangle.spec.reflection))
// 			return (false);
// 		if (!check_specular(&line, &triangle.spec))
// 			return (false);
// 	}
// 	return (true);
// }

bool	triangle_parcer(char *line, t_data *data)
{
	t_triangle	triangle;
	int			i;

	ft_memset(&triangle, 0, sizeof(t_triangle));
	data->counter.triangle += 1;
	line += 3;
	if (!cordinate_parcer(&line, &triangle.cord1, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt:  tr invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &triangle.cord2, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt:  tr invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &triangle.cord3, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt:  tr invalid cordinate format", 2), false);
	line += skip_spaces(line);
	i = color_parcer(line, &triangle.clr);
	if (i == -1)
		return (ft_putendl_fd("minirt: triangle invalid color format", 2), false);
	line += skip_spaces(line + i) + i;
	if (!check_for_features(line, &triangle.spec))
		return (false);
	if (!object_validate(T_TRIANGLE, TRIANGLE, data, &triangle))
		return (false);
	return (true);
}