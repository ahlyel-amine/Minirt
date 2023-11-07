/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cordinate_parcer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:19:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/07 17:20:18 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "structs.h"
# include "libft.h"
# include "tools.h"
# include "library.h"
# include <stdbool.h>

bool	cordinate_parcer(char **line, t_vec *cordinate, int marge_max, int marge_min)
{
	bool	success;

	success = true;
	cordinate->v_x = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	(*line)++;
	cordinate->v_y = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	(*line)++;
	cordinate->v_z = ft_atod(line, &success, marge_max, marge_min);
	if (!success)
		return (false);
	return (true);
}
