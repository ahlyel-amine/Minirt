/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:03:33 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/12 10:21:14 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "minirt.h"
#include "tracer.h"
#include "draw.h"
#include "library.h"
#include <mlx.h>

void	draw(t_data data, t_mrt *scean)
{
	t_hit_record	rec;
	t_rays			rays;

	ft_memset(&rays, 0, sizeof(t_rays));
	ft_bzero(scean->mlx_add, WIDTH * HEIGHT * (scean->bit_per_px / 8));
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			Prime_ray(i, j, &(rays.ray), &data.camera);
			my_mlx_put(scean, i, j, rgb_to_int(raytrace(&data, &rays, &rec)));
		}
	}
	mlx_put_image_to_window(scean->mlx, scean->mlx_win, scean->mlx_img, 0, 0);
}
