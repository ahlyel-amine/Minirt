/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:03:33 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/13 12:27:57 by aelbrahm         ###   ########.fr       */
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
	int				idx[2];

	ft_memset(&rays, 0, sizeof(t_rays));
	ft_bzero(scean->mlx_add, WIDTH * HEIGHT * (scean->bit_per_px / 8));
	*idx = 0;
	while (*idx < HEIGHT)
	{
		*(idx + 1) = -1;
		while (++(*(idx + 1)) < WIDTH)
		{
			prime_ray(*(idx + 1), *idx, &(rays.ray), &data.camera);
			my_mlx_put(scean, *(idx + 1), *idx, \
			rgb_to_int(raytrace(&data, &rays, &rec)));
		}
		(*idx)++;
	}
	mlx_put_image_to_window(scean->mlx, scean->mlx_win, scean->mlx_img, 0, 0);
}
