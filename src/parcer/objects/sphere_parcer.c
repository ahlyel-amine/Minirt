/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parcer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:21:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/01 19:45:31 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/structs.h"
#include "../../../include/parcer.h"
#include "../../../include/tools.h"
#include "../../../include/libft.h"
#include "../../../include/library.h"
#include <stdbool.h>
#include <limits.h>

bool sphere_parcer(char *line, t_data *data)
{
	t_objects	*obejct;
	t_sphere	sphere;
	bool		success;


	(void)data;
	success = true;
	line += 3;
	line += skip_spaces(line);
	if (!cordinate_parcer(&line, &sphere.cord, INT_MAX, INT_MIN))
		return (false);
	line += skip_spaces(line);
	sphere.diameter = ft_atod(&line, &success, INT_MAX, INT_MIN);
	if (!success)
		return (false);
	line += skip_spaces(line);
	if (!color_parcer(line, &sphere.clr))
		return (false);
	obejct = newobject(&sphere, SPHERE);
	addobject_front(&data->objects, obejct);
	return (true);
}
