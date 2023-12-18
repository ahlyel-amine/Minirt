/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parcer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/18 17:33:14 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parcer.h"
#include "tools.h"
#include "libft.h"
#include "library.h"
#include <stdbool.h>
#include <limits.h>

bool	sphere_parcer(char *line, t_data *data)
{
	t_sphere	sphere;

	ft_memset(&sphere, 0, sizeof(t_sphere));
	data->counter.sphere += 1;
	line += 3;
	if (!cordinate_parcer(&line, &sphere.cord, INT_MAX, INT_MIN))
		return (ft_putendl_fd(ERR_SP_CORD, 2), false);
	if (!ft_atod(&line, &sphere.diameter, INT_MAX, INT_MIN))
		return (ft_putendl_fd(ERR_SP_DR, 2), false);
	line += skip_spaces(line);
	if (!color_parcer(line, &sphere.clr))
		return (ft_putendl_fd(ERR_SP_COLOR, 2), false);
	if (!object_validate(T_SPHERE, SPHERE, data, &sphere))
		return (false);
	return (true);
}
