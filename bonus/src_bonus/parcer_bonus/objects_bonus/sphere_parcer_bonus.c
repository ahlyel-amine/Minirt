/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parcer_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/15 23:25:28 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>

bool sphere_parcer(line, data)
char *line;
t_data *data;
{
	t_sphere	sphere;
	int			i;

	ft_memset(&sphere, 0, sizeof(t_sphere));
	data->counter.sphere += 1;
	line += 3;
	if (!cordinate_parcer(&line, &sphere.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: sp invalid cordinate format", 2), false);
	if (!ft_atod(&line, &sphere.diameter, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: invalid diameter format", 2), false);
	line += skip_spaces(line);
	i = color_parcer(line, &sphere.clr);
	if (i == -1)
		return (ft_putendl_fd("minirt: sphere invalid color format", 2), false);
	line += skip_spaces(line + i) + i;
	if (!check_for_features(line, &sphere.spec))
		return (false);
	if (!object_validate(T_SPHERE, SPHERE, data, &sphere))
		return (false);
	return (true);
}
