/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cordinate_parcer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:19:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/01 19:34:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/structs.h"
#include "../../include/libft.h"
#include "../../include/tools.h"
#include "../../include/library.h"
#include <stdbool.h>

bool	cordinate_parcer(char **line, t_cord *cordinate, int marge_max, int marge_min)
{
	bool	success;


	success = true;
	*line += skip_spaces(*line);
	cordinate->x = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	(*line)++;
	*line += skip_spaces(*line);
	cordinate->y = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	(*line)++;
	*line += skip_spaces(*line);
	cordinate->z = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	return (true);
}
