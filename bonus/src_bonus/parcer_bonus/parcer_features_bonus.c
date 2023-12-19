/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_features_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:52:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/19 20:02:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>
#include <limits.h>

bool	check_reflection(char **line, double *reflection, bool *loop)
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, S_REF, 2))
	{
		*line += 2;
		if (!ft_atod(line, reflection, 1, 0))
			return (print_err(4, ERR, NAME, ERR_V, ERR_REF), false);
		*loop = true;
	}
	*line += skip_spaces(*line);
	return (true);
}

bool	check_specular(char **line, t_specular_light *specular, bool *loop)
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 2 && !ft_strncmp(*line, S_SPEC, 2))
	{
		*line += 2;
		if (!ft_atod(line, &specular->intensity, 10, 0))
			return (print_err(5, ERR, NAME, \
			ERR_SPEC, ERR_V, ERR_INT), false);
		if (*line[0] == ':')
			*line += 1;
		else
			return (print_err(4, ERR, NAME, ERR_F, ERR_SPEC), false);
		if (!ft_atod(line, &specular->shininess_factor, 1, 0))
			return (print_err(5, ERR, NAME, \
			ERR_SPEC, ERR_V, ERR_SHF), false);
		*loop = true;
	}
	*line += skip_spaces(*line);
	return (true);
}

bool	check_checkerboard(char **line, t_specular_light *checkred, bool *loop)
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 9 && !ft_strncmp(*line, S_CHKBRD, 9))
	{
		*line += 9;
		if (!ft_atod(line, &checkred->checkred_h, INT_MAX, INT_MIN))
			return (print_err(5, ERR, NAME, \
			ERR_CHKBRD, ERR_V, ERR_HT), false);
		if (**line == ':')
			(*line)++;
		else
			return (print_err(4, ERR, NAME, ERR_F, ERR_CHKBRD), false);
		if (!ft_atod(line, &checkred->checkred_w, INT_MAX, INT_MIN))
			return (print_err(5, ERR, NAME, \
			ERR_CHKBRD, ERR_V, ERR_WH), false);
		checkred->checkred = true;
		*loop = true;
	}
	*line += skip_spaces(*line);
	return (true);
}

bool	get_path(char **line, char **texture)
{
	int	i;

	i = 0;
	while (ft_strlen(*line + i) >= 5 && ft_strncmp(*line + i, S_XPM, 5))
		i++;
	if (!ft_strncmp(*line + i, S_XPM, 5))
	{
		*texture = ft_substr(*line, 0, i + 4);
		*line += i + 5;
		return (true);
	}
	return (false);
}

bool	check_texture(char **line, char **texture, bool *loop, char *ind)
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

bool	textures_call(char **line, t_specular_light *spec, bool *loop)
{
	if (!check_texture(line, &spec->texture, loop, S_TXTR))
		return (false);
	if (*loop)
		return (true);
	if (!check_texture(line, &spec->bump, loop, S_BUMP))
		return (false);
	return (true);
}

bool	check_for_features(char *line, t_specular_light *spec)
{
	bool	loop;

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
		if (!textures_call(&line, spec, &loop))
			return (false);
		if (!loop)
			break ;
	}
	if (*line)
		return (print_err(4, ERR, NAME, ERR_F, "\n"), false);
	return (true);
}
