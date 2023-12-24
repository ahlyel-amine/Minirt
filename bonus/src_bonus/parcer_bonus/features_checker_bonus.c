/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features_checker_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:02:33 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/24 16:09:38 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
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

bool	check_specular(char **line, t_features *specular, bool *loop)
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

bool	check_checkerboard(char **line, t_features *checkred, \
bool *loop, int type)
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 9 && !ft_strncmp(*line, S_CHKBRD, 9))
	{
		if (type != SPHERE && type != CYLENDER && type != PLANE)
			return (print_err(4, ERR, NAME, ERR_F, ERR_CKRD), false);
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

bool	check_texture(char **line, char **texture, bool *loop, char *ind)
{
	*line += skip_spaces(*line);
	if (ft_strlen(*line) >= 6 && !ft_strncmp(*line, ind, 6))
	{
		if (ft_strlen(ind) == 7)
			return (print_err(4, ERR, NAME, ERR_F, ERR_TXTR), false);
		*line += 6;
		if (!get_path(line, texture))
			return (false);
		*loop = true;
	}
	*line += skip_spaces(*line);
	return (true);
}
