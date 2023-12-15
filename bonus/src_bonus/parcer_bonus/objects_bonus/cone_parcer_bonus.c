/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parcer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/15 16:01:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "parcer_bonus.h"
#include "tools_bonus.h"
#include "libft.h"
#include "vector_bonus.h"
#include "library_bonus.h"
#include <stdbool.h>
#include <limits.h>



bool cone_parcer(char *line, t_data *data)
{
	t_objects	*object;
	t_cone	*cone;
	t_cone	single_cone;

	data->counter.cone += 1;
	line += 3;
	ft_memset(&single_cone, 0, sizeof(t_cone));
	if (!cordinate_parcer(&line, &single_cone.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt:  cn invalid cordinate format", 2), false);
	if (!cordinate_parcer(&line, &single_cone.normalized, 1, -1))
		return (ft_putendl_fd("minirt: invalid normalized format", 2), false);
	if (!ft_atod(&line, &single_cone.half_angle, 180, 0))
		return (ft_putendl_fd("minirt: invalid half angle format", 2), false);
	if (!ft_atod(&line, &single_cone.height, INT_MAX, INT_MIN))
		return (ft_putendl_fd("minirt: invalid height format", 2), false);
	line += skip_spaces(line);
	int a = color_parcer(line, &single_cone.clr);
	if (a == -1)
		return (ft_putendl_fd("minirt: cone invalid color format", 2), false);
	line += skip_spaces(line + a) + a;
	if (!check_for_features(line, &single_cone.spec))
		return (false);
	object_validate(T_CONE, CONE, data, &single_cone);
	return (true);
}
