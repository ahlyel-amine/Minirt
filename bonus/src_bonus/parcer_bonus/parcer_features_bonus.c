/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_features_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:52:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/25 17:38:41 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include <mlx.h>
#include <limits.h>

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

bool	textures_call(char **line, t_features *spec, bool *loop, int type)
{
	char	*s;
	bool	check;

	check = type != SPHERE && type != CYLENDER && type != PLANE;
	s = (char *)((unsigned long)S_ERR_TXTR * \
	check + (unsigned long)S_TXTR * !check);
	if (!check_texture(line, &spec->texture, loop, s))
		return (false);
	if (*loop)
		return (true);
	s = (char *)((unsigned long)S_ERR_BUMP * \
	check + (unsigned long)S_BUMP * !check);
	if (!check_texture(line, &spec->bump, loop, s))
		return (false);
	return (true);
}

bool	features_parcer(char *line, t_features *spec, int type)
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
		if (!check_checkerboard(&line, spec, &loop, type))
			return (false);
		if (loop)
			continue ;
		if (!textures_call(&line, spec, &loop, type))
			return (false);
		if (!loop)
			break ;
	}
	if (*line)
		return (print_err(4, ERR, NAME, ERR_F, "\n"), false);
	return (true);
}
