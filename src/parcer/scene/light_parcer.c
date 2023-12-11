/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parcer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:23:47 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/11 17:29:03 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parcer.h"
#include "tools.h"
#include "libft.h"
#include "library.h"
#include <stdbool.h>
#include <limits.h>

bool light_parcer(char *line, t_data *data)
{
	static	bool	visited;
	t_light	*light;
	t_light	single_light;
	
	if (visited)
		return (ft_putendl_fd("minirt: error: duplicate of light information", 2), false);
	visited = true;
	line += 2;
	if (!cordinate_parcer(&line, &data->light.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: light invalid cordinate format", 2), false);
	if (!ft_atod(&line, &data->light.brightness, 1, 0))
		return (ft_putendl_fd("minirt: light invalid brightness format", 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &data->light.clr))
		return (ft_putendl_fd("minirt: light invalid color format", 2), false);
	return (true);
}
