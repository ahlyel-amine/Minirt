/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/29 20:42:34 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"
#include "libft.h"
#include "library.h"
#include "tools.h"
#include <mlx.h>

bool	make_image(t_mrt *scean)
{
	scean->mlx = mlx_init();
	if (!scean->mlx)
		return (false);
	scean->mlx_win = mlx_new_window(scean->mlx, WIDTH, HEIGHT, "MINI_RT");
	if (!scean->mlx_win)
		return (false);
	scean->mlx_img = mlx_new_image(scean->mlx, WIDTH, HEIGHT);
	if (!scean->mlx_img)
		return (false);
	scean->mlx_add = mlx_get_data_addr(scean->mlx_img, \
	&(scean->bit_per_px), &(scean->line_len), &(scean->endian));
	if (!scean->mlx_add)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_mrt		scean;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (!parcer(av[1], &data))
			return (clearobjs(&data.objects), 1);
		if (!make_image(&scean))
			return (clearobjs(&data.objects), 1);
		data.m_rt = &scean;
		lookat(&data.camera);
		draw(data, &scean);
		hooks_settings(&data);
		mlx_loop(scean.mlx);
	}
	return (0);
}
