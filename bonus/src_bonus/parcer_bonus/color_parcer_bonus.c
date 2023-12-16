/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parcer_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:19:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/16 14:08:26 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "tools_bonus.h"
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

static bool	check_rgb(char *rgb, int *i)
{
	int	j;
	int	total;

	*i = 0;
	*i = only_3_digits(rgb);
	if (*i == -1 || rgb[*i] != ',')
		return (false);
	j = only_3_digits(rgb + *i + 1);
	*i += j + 1;
	if (j == -1 || rgb[*i] != ',')
		return (false);
	j = only_3_digits(rgb + *i + 1);
	*i += j + 1;
	if (j == -1)
		return (false);
	return (true);
}

int	color_parcer(char *line, t_color *color)
{
	char	**colors;
	int		tmp;
	int		i;
	int		ret;

	i = 0;
	if (!check_rgb(line, &ret))
		return (-1);
	colors = ft_split(line, ',');
	if (!colors)
		return (free(line), -1);
	while (i < 3 && colors[i])
	{
		tmp = ft_atoi(colors[i]);
		if (tmp > 255 || tmp < 0)
			ret = -1;
		*(&color->r + (i * sizeof(unsigned char))) = tmp;
		free (colors[i++]);
	}
	return (free(colors), ret);
}
