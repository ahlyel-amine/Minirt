/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cordinate_parcer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:19:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 11:47:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "structs_bonus.h"
# include "libft.h"
# include "tools_bonus.h"
# include "library_bonus.h"
# include <stdbool.h>

bool	cordinate_parcer(char **line, t_vec *cordinate, int marge_max, int marge_min)
{
	if (!ft_atod(line, &cordinate->v_x, marge_max, marge_min))
		return (false);
	(*line)++;
	if (!ft_atod(line, &cordinate->v_y, marge_max, marge_min))
		return (false);
	(*line)++;
	if (!ft_atod(line, &cordinate->v_z, marge_max, marge_min))
		return (false);
	return (true);
}
