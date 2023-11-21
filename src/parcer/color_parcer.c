/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:19:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/17 09:45:10 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "tools.h"
#include <stdbool.h>

static int	only_3_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]) && i < 5)
		i++;
	if (i > 0 && i < 4)
		return (i);
	return (-1);
}

static bool	check_rgb(char *rgb)
{
	int	i;
	int	j;

	i = 0;
	i = only_3_digits(rgb);
	if (i == -1 || rgb[i] != ',')
		return (ft_putendl_fd("minirt: invalid color format", 2), false);
	j = only_3_digits(rgb + i + 1);
	i += j + 1;
	if (j == -1 || rgb[i] != ',')
		return (ft_putendl_fd("minirt: invalid color format", 2), false);
	j = only_3_digits(rgb + i + 1);
	i += j + 1;
	if (j == -1)
		return (ft_putendl_fd("minirt: invalid color format", 2), false);
	else if (rgb[i + skip_spaces(rgb + i)])
		return (ft_putendl_fd("color minirt: to much argumets", 2), false);
	return (true);
}

bool	color_parcer(char *line, t_color *color)
{
	char	**colors;
	int		tmp;
	int		i;
	bool	ret;

	i = 0;
	ret = true;
	if (!check_rgb(line))
		return (false);
	colors = ft_split(line, ',');
	if (!colors)
		return (free(line), false);
	while (i < 3 && colors[i])
	{
		tmp = ft_atoi(colors[i]);
		if (tmp > 255 || tmp < 0)
			ret = false;
		*(&color->r + (i * sizeof(unsigned char))) = tmp;
		free (colors[i++]);
	}
	return (free(colors), ret);
}
