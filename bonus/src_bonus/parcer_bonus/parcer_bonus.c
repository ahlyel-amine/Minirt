/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:09:57 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/04 18:20:54 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "minirt_bonus.h"
#include "structs_bonus.h"
#include "get_next_line.h"
#include "tools_bonus.h"
#include "library_bonus.h"
#include "libft.h"
#include "parcer_bonus.h"

enum types	find_type(char *line)
{
	if (!ft_strncmp(line, S_LIGHTING, 1) && ft_isspace(line[1]))
		return (LIGHTING);
	else if (!ft_strncmp(line, S_LIGHT, 1) && ft_isspace(line[1]))
		return (LIGHT);
	else if (!ft_strncmp(line, S_CAMERA, 1) && ft_isspace(line[1]))
		return (CAMERA);
	else if (!ft_strncmp(line, S_SPHERE, 2) && ft_isspace(line[2]))
		return (SPHERE);
	else if (!ft_strncmp(line, S_CYLENDER, 2) && ft_isspace(line[2]))
		return (CYLENDER);
	else if (!ft_strncmp(line, S_PLANE, 2) && ft_isspace(line[2]))
		return (PLANE);
	else if (!ft_strncmp(line, S_TRIANGLE, 2) && ft_isspace(line[2]))
		return (TRIANGLE);
	else if (!ft_strncmp(line, S_CONE, 2) && ft_isspace(line[2]))
		return (CONE);
	else
		return (INVALID);
}

object_parcer	objcets_parcers(enum types offset)
{
	static object_parcer	function_parcer[MAX_OBJECTS];
	static bool				init;

	if (!init)
	{
		init = true;
		function_parcer[SPHERE] = sphere_parcer;
		function_parcer[CYLENDER] = cylender_parcer;
		function_parcer[PLANE] = plane_parcer;
		function_parcer[LIGHTING] = lighting_parcer;
		function_parcer[CAMERA] = camera_parcer;
		function_parcer[LIGHT] = light_parcer;
		function_parcer[TRIANGLE] = triangle_parcer;
		function_parcer[CONE] = cone_parcer;
	}
	return (*(function_parcer + offset));
}

bool	transform_line(char *line, t_data *data)
{
	enum types		type;

	if (!line[skip_spaces(line)])
		return (true);
	if (line[skip_spaces(line)] == '#')
		return (true);
	type = find_type(line);
	if (type == INVALID)
		return (ft_putendl_fd("minirt: invalid object/description format", 2), false);
	if (!objcets_parcers(type)(line, data))
		return (false);
	return (true);
}

bool	read_true(char **line, t_data *data, int fd)
{
	while (*line)
	{
		if (!transform_line(*line, data))
			return (false);
		free (*line);
		*line = get_next_line(fd);
	}
	return (true);
}

bool	parcer(char *scene, t_data	*data)
{
	int		fd;
	char	*line;

	fd = open(scene, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (ft_putendl_fd("minirt: invalid scene file", 2), false);
	line = get_next_line(fd);
	if (!line)
		return (ft_putendl_fd("minirt: empty scene file", 2), false);
	if (!read_true(&line, data, fd))
		return (false);
	return (true);
}