/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:09:57 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/01 19:28:43 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "../../include/minirt.h"
#include "../../include/structs.h"
#include "../../include/get_next_line.h"
#include "../../include/tools.h"
#include "../../include/library.h"
#include "../../include/libft.h"
#include "../../include/parcer.h"

enum types	find_type(char *line)
{
	if (!ft_strncmp(line, S_LIGHTING, ft_strlen(S_LIGHTING)))
		return (LIGHTING);
	else if (!ft_strncmp(line, S_LIGHT, ft_strlen(S_LIGHT)))
		return (LIGHT);
	else if (!ft_strncmp(line, S_CAMERA, ft_strlen(S_CAMERA)))
		return (CAMERA);
	else if (!ft_strncmp(line, S_SPHERE, ft_strlen(S_SPHERE)))
		return (SPHERE);
	else if (!ft_strncmp(line, S_CYLENDER, ft_strlen(S_CYLENDER)))
		return (CYLENDER);
	else if (!ft_strncmp(line, S_PLANE, ft_strlen(S_PLANE)))
		return (PLANE);
	else
		return (INVALID);
}

object_parcer	objcets_parcers(enum types call)
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
	}
	return (*(function_parcer + call));
}

bool	transform_line(char *line, t_data *data)
{
	enum types		type;

	if (!line[skip_spaces(line)])
		return (true);
	type = find_type(line);
	if (type == INVALID)
		return (ft_putendl_fd("minirt: invalid object/function format", 2), false);
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
		free(*line);
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
		ft_putendl_fd("minirt: invalid scene file", 2);
	line = get_next_line(fd);
	if (!line)
		ft_putendl_fd("minirt: empty scene file", 2);
	if (!read_true(&line, data, fd))
		return (false);
	return (true);
}
