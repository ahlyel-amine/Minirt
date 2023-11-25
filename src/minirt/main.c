/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/25 07:30:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"
#include "vector.h"
#include "draw.h"
#include "tools.h"
#include "MLX42.h"
#include <pthread.h>
// #include <mlx.h>

// t_coord	ray_color(t_ray *ray, t_objects *obj, t_hit_record *rec)
// {
		
// 	if (obj->type == SPHERE &&  sphere_hit(ray, (t_sphere*)obj->object, rec))
// 	{
// 		t_sphere *sphere = (t_sphere *)obj->object;
// 		t_vec	n = vec_sub(rec->nHit, sphere->cord);
// 		return (scalar_mult((t_coord){n.v_x + 1, n.v_y + 1, n.v_z + 1}, 0.5));
// 	}
// 	else if (obj->type == PLANE && plan_hit(ray, (t_plane*)obj->object, rec))
// 		return ((t_coord){0.5, 0.5, 0.5});
		
// 	t_coord	unit_direction = normalized(ray->direction);
// 	double t = 0.5 * (unit_direction.v_y + 1.0);
// 	t_coord	c_start = scalar_mult((t_coord){1.0,1.0,1.0}, (1.0 - t));
// 	t_coord	c_end = scalar_mult((t_coord){0.5, 0.7, 1.0}, t);
// 	return (scalar_mult((t_coord){0.3,0.3,0.3}, (0.1)));
// }






bool	make_image(t_mrt *scean)
{
	scean->mlx_win = mlx_init(WIDTH, HEIGHT, "MINI_RT", 1);
	if (!scean->mlx_win)
		return (false);
	// scean->mlx_win = mlx_new_window(scean->mlx, WIDTH, HEIGHT, "MINI_RT");
	// if (!scean->mlx_win)
		// return (false);
	scean->mlx_add = mlx_new_image(scean->mlx_win, WIDTH, HEIGHT);
	if (!scean->mlx_add)
		return (false);
	// scean->mlx_add = mlx_get_data_addr(scean->mlx_img, &(scean->bit_per_px), &(scean->line_len), &(scean->endian));
	// if (!scean->mlx_add)
	// 	return (false);
	return (true);
}

int main(int ac, char **av)
{
	t_data		data;
	pthread_t	th[10];
	t_dataset	ptr[10];
	t_mrt		scean;

	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (!parcer(av[1], &data))
			return (clearobjs(&data.objects),  1);
		print_scean(data);
		printf("sphers:%d cylenders:%d planes:%d\n", data.counter.sphere, data.counter.cylender, data.counter.plane);
		if (!make_image(&scean))
			return (clearobjs(&data.objects),  1);
		lookat(&scean, &data.camera);
		if (!make_threads(&scean, data))
			return (clearobjs(&data.objects),  1);
		mlx_image_to_window(scean.mlx_win, scean.mlx_add,  0, 0);
		// mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int32_t x, int32_t y);
		mlx_loop(scean.mlx_win);
	}
	return 0;
}
