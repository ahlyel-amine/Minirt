/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parcer_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/29 19:44:58 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer_bonus.h"
#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool	check_reflection(line, reflection, loop)
char **line;
double *reflection;
bool	*loop;
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, "r=", 2))
	{
		printf("found r=\n");
		*line += 2;
		if (!ft_atod(line, reflection, 1, 0))
			return (ft_putendl_fd("minirt: invalid reflection", 2), false);
		*loop = true;
	}
	*line += skip_spaces(*line);
	return (true);
}

bool	check_specular(line, specular, loop)
char **line;
t_specular_light	*specular;
bool	*loop;
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, "s=", 2))
	{
		printf("found s=\n");
		*line += 2;
		if (!ft_atod(line, &specular->intensity, 1, 0))
			return (ft_putendl_fd("minirt: invalid specular intensity", 2), false);
		if (**line == ',')
			(*line)++;
		else
			return (ft_putendl_fd("minirt: invalid specular format", 2), false);
		if (!ft_atod(line, &specular->shininess_factor, 1, 0))
			return (ft_putendl_fd("minirt: invalid specular shininess factor", 2), false);
		*loop = true;
	}
	*line += skip_spaces(*line);
	return (true);
}

void	check_checkerboard(line, checkred, loop)
char **line;
bool	*checkred;
bool	*loop;
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 8 && !ft_strncmp(*line, "checkred", 8))
	{
		printf("found checkred\n");
		*line += 8;
		*checkred = true;
		*loop = true;
	}
	*line += skip_spaces(*line);
}

bool	check_for_features(line, spec)
char *line;
t_specular_light *spec;
{
	bool loop;

	while (line)
	{
		loop = false;
		printf("[%s]\n", line);
		if (!check_reflection(&line, &spec->reflection, &loop))
			return (false);
		if (loop)
			continue ;
		if (!check_specular(&line, spec, &loop))
			return (false);
		if (loop)
			continue ;
		check_checkerboard(&line, &spec->checkred, &loop);
		if (loop)
			continue ;
		break ;
	}
	if (*line)
		return (ft_putendl_fd("minirt: plane invalid formatrr", 2), false);
	return (true);
}

bool plane_parcer(char *line, t_data *data)
{
	t_objects	*object;
	t_plane		*plane;

	plane = ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		return (false);
	data->counter.plane += 1;
	line += 3;
	if (!cordinate_parcer(&line, &plane->cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: pl invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &plane->normalized, 1, -1))
		return (ft_putendl_fd("minirt: invalid normalized format", 2), false);
	line += skip_spaces(line);
	int a = color_parcer(line, &plane->clr);
	if (a == -1)
		return (ft_putendl_fd("minirt: plane invalid color format", 2), false);
	line += skip_spaces(line + a) + a;
	// ft_atod(&line, &plane->spec.intensity, INT_MAX, INT_MIN);
	// 	// return (ft_putendl_fd("minirt: plane invalid intensity", 2), false);
	// line += skip_spaces(line);
	// ft_atod(&line, &plane->spec.shininess_factor, 1, 0);
	// 	// return (ft_putendl_fd("minirt: plane invalid shininess factor", 2), false);
	// line += skip_spaces(line);
	// ft_atod(&line, &plane->spec.reflection, 1, 0);
	// 	// return (ft_putendl_fd("minirt: plane invalid reflection", 2), false);
	if (!check_for_features(line, &plane->spec))
		return (false);
	// line += skip_spaces(line);
	// if (ft_strlen(line) >= 8 && !ft_strncmp(line, "checkred", 8))
	// {
	// 	line += 8;
	// 	plane->spec.checkred = true;
	// }
	// line += skip_spaces(line);
	// if (*line)
	// 	return (ft_putendl_fd("minirt: plane invalid formats", 2), false);
	object = newobject(plane, PLANE);
	if (!object)
		return (false);  
	addobject_front(&data->objects, object);
	return (true);
}
