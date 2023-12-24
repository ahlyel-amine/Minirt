/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/24 01:34:47 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "libft.h"
#include "tools_bonus.h"
#include "vector_bonus.h"
#include "library_bonus.h"
#include "draw_bonus.h"
#include <mlx.h>

bool	make_image(t_mrt *scean)
{
	scean->mlx = mlx_init();
	if (!scean->mlx)
		return (false);
	scean->mlx_win = mlx_new_window(scean->mlx, WIDTH, HEIGHT, "MiniRT_BONUS");
	if (!scean->mlx_win)
		return (false);
	scean->mlx_img = mlx_new_image(scean->mlx, WIDTH, HEIGHT);
	if (!scean->mlx_img)
		return (false);
	scean->mlx_add = mlx_get_data_addr(scean->mlx_img, &(scean->bit_per_px), \
	&(scean->line_len), &(scean->endian));
	if (!scean->mlx_add)
		return (false);
	return (true);
}

void	check(void)
{
	system("leaks Minirt_bonus");
}

int	main(int ac, char **av)
{
	t_data		data;
	t_mrt		scean;

	atexit(check);
	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (!parcer(av[1], &data))
			return (clearobjs(&data.objects), clearlights(&data.light), 1);
		if (!make_image(&scean))
			return (clearobjs(&data.objects), clearlights(&data.light), 1);
		lookat(&data.camera);
		data.m_rt = &scean;
		data.load_p = 0;
		textures_binding(data.objects, &scean);
		if (!make_threads(&scean, data))
			return (clearobjs(&data.objects), clearlights(&data.light), 1);
		hooks_settings(&data);
		mlx_loop(scean.mlx);
	}
	return (0);
}
