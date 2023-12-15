/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_features_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:52:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/15 13:13:03 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>
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
		*line += 2;
		printf("found s=%s\n", *line);
		if (!ft_atod(line, &specular->intensity, 10, 0))
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

bool	check_checkerboard(line, checkred, loop)
char **line;
t_specular_light	*checkred;
bool	*loop;
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 9 && !ft_strncmp(*line, "checkred=", 9))
	{
		printf("found checkred\n");
		*line += 9;
		if (!ft_atod(line, &checkred->checkred_h, INT_MAX, INT_MIN))
			return (ft_putendl_fd("minirt: invalid checkred height", 2), false);
		if (**line == ',')
			(*line)++;
		else
			return (ft_putendl_fd("minirt: invalid checkred format", 2), false);
		if (!ft_atod(line, &checkred->checkred_w, INT_MAX, INT_MIN))
			return (ft_putendl_fd("minirt: invalid checkred width factor", 2), false);
		checkred->checkred = true;
		*loop = true;
	}
	*line += skip_spaces(*line);
	return (true);
}

bool	get_path(line, texture)
char	**line;
char	**texture;
{
	int i;

	i = 0;
	while (ft_strlen(*line + i) >= 5 && ft_strncmp(*line + i, ".xpm\"", 5))
		i++;
	if (!ft_strncmp(*line + i, ".xpm\"", 5))
	{
		*texture = ft_substr(*line, 0, i + 4);
		*line += i + 5;
		return (true);
	}
	return (false);
}

bool	check_texture(line, texture, loop, ind)
char **line;
char	**texture;
bool	*loop;
char	*ind;
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 6 && !ft_strncmp(*line, ind, 6))
	{
		*line += 6;
		if (!get_path(line, texture))
			return (false);
		*loop = true;
	}
	*line += skip_spaces(*line);
	return (true);
}

bool	check_for_features(line, spec)
char *line;
t_specular_light *spec;
{
	bool loop;

	while (line)
	{
		loop = false;
		if (!check_reflection(&line, &spec->reflection, &loop))
			return (false);
		if (loop)
			continue ;
		if (!check_specular(&line, spec, &loop))
			return (false);
		if (loop)
			continue ;
		if (!check_checkerboard(&line, spec, &loop))
			return (false);
		if (loop)
			continue ;
		check_texture(&line, &spec->texture, &loop, "txtr=\"");
		check_texture(&line, &spec->bump, &loop, "bump=\"");
		if (loop)
			continue ;
		break ;
	}
	if (*line)
		return (ft_putendl_fd("minirt: invalid format", 2), false);
	return (true);
}
