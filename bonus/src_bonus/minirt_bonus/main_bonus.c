/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/01 19:01:05 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "minirt_bonus.h"
#include "libft.h"
#include "tools_bonus.h"
#include "vector_bonus.h"
#include "library_bonus.h"
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
	scean->mlx_add = mlx_get_data_addr(scean->mlx_img, &(scean->bit_per_px), &(scean->line_len), &(scean->endian));
	if (!scean->mlx_add)
		return (false);
	return (true);
}

int main(int ac, char **av)
{
	t_data		data;
	t_mrt		scean;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (!parcer(av[1], &data))
			return (clearobjs(&data.objects), clearlights(&data.light),  1);
		print_scean(data);
		if (!make_image(&scean))
			return (clearobjs(&data.objects), clearlights(&data.light),  1);
		lookat(&data.camera);
		if (!make_threads(&scean, data))
			return (clearobjs(&data.objects), clearlights(&data.light),  1);
		mlx_put_image_to_window(scean.mlx, scean.mlx_win, scean.mlx_img, 0, 0);
		mlx_loop(scean.mlx);
	}
	return 0;
}
