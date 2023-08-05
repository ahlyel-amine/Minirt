/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cordinate_parcer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:19:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/05 01:30:11 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "tools.h"
#include "library.h"
#include <stdbool.h>

bool	cordinate_parcer(char **line, t_cord *cordinate, int marge_max, int marge_min)
{
	bool	success;

	success = true;
	cordinate->x = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	(*line)++;
	cordinate->y = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	(*line)++;
	cordinate->z = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	return (true);
}
