/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:03:33 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/27 16:04:13 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	draw(t_data data, t_mrt *scean)
{
	t_hit_record	rec;
	t_rays			rays;

	ft_memset(&rays, 0, sizeof(t_rays));
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			Prime_ray(scean, i, j, &(rays.ray), &data.camera);
			my_mlx_put(scean, i, j, rgb_to_int(raytrace(&data, &rays, &rec)));
		}
	}
}
