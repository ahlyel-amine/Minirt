/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/03 21:07:27 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"

int main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (!parcer(av[1], &data))
		{
			return (1);
		}
		while (data.objects)
		{
			if (data.objects->type == SPHERE)
			{
				t_sphere	*object = (t_sphere *)data.objects->object;
				printf("sphere\t:\t%.1f,%.1f,%.1f\t%.1f\t\t\t\t%d,%d,%d\n", object->cord.x, object->cord.y, object->cord.z, object->diameter, object->clr.r, object->clr.g, object->clr.b);
			}
			else if (data.objects->type == PLANE)
			{
				t_plane	*object = (t_plane *)data.objects->object;
				printf("plane\t:\t%.1f,%.1f,%.1f\t%.1f,%.1f,%.1f\t\t\t%d,%d,%d\n", object->cord.x, object->cord.y, object->cord.z, object->normalized.x, object->normalized.y, object->normalized.z, object->clr.r, object->clr.g, object->clr.b);
			}
			else if (data.objects->type == CYLENDER)
			{
				t_cylender	*object = (t_cylender *)data.objects->object;
				printf("cylender:\t%.1f,%.1f,%.1f\t%.1f,%.1f,%.1f\t%.1f\t%.1f\t%d,%d,%d\n", object->cord.x, object->cord.y, object->cord.z, object->normalized.x, object->normalized.y, object->normalized.z, \
				object->diameter, object->height,  object->clr.r, object->clr.g, object->clr.b);
			}
			data.objects = data.objects->next;
		}
	}
	return 0;
}
