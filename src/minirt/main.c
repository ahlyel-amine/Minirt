/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 04:41:56 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/28 07:03:46 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "library.h"
#include "minirt.h"
#include "vector.h"
#include <mlx.h>
#define WIDTH 900
#define HEIGHT 600
void	clearobjs(t_objects **lst)
{
	t_objects	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free ((*lst)->object);
		free(*lst);
		*lst = tmp;
	}
}
void	my_mlx_put(t_mrt *rt, int x, int y, int color)
{
	int	iter;

	if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
	{
		iter = (x * rt->bit_per_px / 8) + (y * rt->line_len);
		rt->mlx_add[iter] = color;
		rt->mlx_add[++iter] = (color >> 8) & 0xFF;
		rt->mlx_add[++iter] = (color >> 16) & 0xFF;
	
	}
	return ;
}

void	Prime_ray(t_mrt *rt ,int x, int y, t_ray *ray,t_camera *cam)
{
	double ndcX;
	double ndcY;
	t_vec	direction;
	double 	aspect_ratio = WIDTH / (double)HEIGHT;
	ray->origin = create_vec_from_scalar(0);
	ndcX = ((double)x + 0.5) / WIDTH;
	ndcY = ((double)y + 0.5) / HEIGHT;
	// my_mlx_put(rt, (int)ndcX, (int)ndcY, 0xFF0000);
	// printf("%.4f  %.4f\n", ndcX, ndcY);
	direction.v_x = (2 * ndcX - 1) * tan(((int)(cam->v_field) >> 1) * M_PI / 180) * aspect_ratio;
	direction.v_y = (1 - 2 * ndcY) * tan(((int)(cam->v_field) >> 1) * M_PI / 180);
	direction.v_z = -1.0;
	
	ray->direction = direction;
	printf("%.8f %.8f %.8f\n", ray->direction.v_x, ray->direction.v_y, ray->direction.v_z);

}

int Intersect(t_sphere sphere, t_ray ray, t_vec *pHit, t_vec *nHit) {
    t_vec oc = { ray.origin.v_x - sphere.cord.v_x, ray.origin.v_y - sphere.cord.v_y, ray.origin.v_z - sphere.cord.v_z };
    double a = dot_product(ray.direction, ray.direction);
    double b = 2.0f * dot_product(oc, ray.direction);
    double c = dot_product(oc, oc) - ((sphere.diameter / 2) * (sphere.diameter / 2));
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0f * a);
        double t = (t1 < t2) ? t1 : t2;

        pHit->v_x = ray.origin.v_x + t * ray.direction.v_x;
        pHit->v_y = ray.origin.v_y + t * ray.direction.v_y;
        pHit->v_z = ray.origin.v_z + t * ray.direction.v_z;

        *nHit = normalize(pHit);
        return 1;
    }

    return 0;
}
void	draw(t_mrt *m_rt, t_ray *ray, t_camera *cam)
{
	int	x;
	int	y;
	// t_camera *cam = (t_camera *)data.objects->object;
	t_sphere sphere = {{0.0,0.0,20.6}, 70.6, {10,0,255}};
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// puts("alo");
			Prime_ray(m_rt, x, y, ray, cam);
			t_vec pHit, nHit;
			double minDistance = INFINITY;
			if (Intersect(sphere, *ray, &pHit, &nHit))
				my_mlx_put(m_rt, (int)x, (int)y, 0xff00);
			else
				my_mlx_put(m_rt, (int)x, (int)y, 0xffff);

			// printf("%.8f  %.8f %.8f\n", ray->direction.v_x, ray->direction.v_x, ray->direction.v_x);
			// usleep(10000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(m_rt->mlx, m_rt->mlx_win, m_rt->mlx_img, 0, 0);
}

int main(int ac, char **av)
{
	t_data	data;
	t_camera	*cam;
	ft_memset(&data, 0, sizeof(t_data));
	if (ac == 2)
	{
		if (!parcer(av[1], &data))
			return (clearobjs(&data.objects),  1);
		printf("cy's : %d, pl's : %d, sp's : %d\n", data.counter.cylender, data.counter.plane, data.counter.sphere);
		while (data.objects)
		{
			if (data.objects->type == SPHERE)
			{
				t_sphere	*object = (t_sphere *)data.objects->object;
				printf("sphere\t:\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t%d,%d,%d\n", object->cord.v_x, object->cord.v_y, object->cord.v_z, object->diameter, object->clr.r, object->clr.g, object->clr.b);
			}
			else if (data.objects->type == PLANE)
			{
				t_plane	*object = (t_plane *)data.objects->object;
				printf("plane\t:\t%.1f,%.1f,%.1f\t%.1f,%.1f,%.1f\t\t\t%d,%d,%d\n", object->cord.v_x, object->cord.v_y, object->cord.v_z, object->normalized.v_x, object->normalized.v_y, object->normalized.v_z, object->clr.r, object->clr.g, object->clr.b);
			}
			else if (data.objects->type == CYLENDER)
			{
				t_cylender	*object = (t_cylender *)data.objects->object;
				printf("cylender:\t%.1f,%.1f,%.1f\t%.1f,%.1f,%.1f\t%.1f\t%.1f\t%d,%d,%d\n", object->cord.v_x, object->cord.v_y, object->cord.v_z, object->normalized.v_x, object->normalized.v_y, object->normalized.v_z, \
				object->diameter, object->height,  object->clr.r, object->clr.g, object->clr.b);
			}
			else if (data.objects->type == CAMERA)
			{
				t_camera	*object = (t_camera *)data.objects->object;
				cam = object;
				printf("camera\t:\t%.1f,%.1f,%.1f\t%.1f,%.1f,%.1f\t\t%d\n", object->cord.v_x, object->cord.v_y, object->cord.v_z, object->normalized.v_x, object->normalized.v_y, object->normalized.v_z, \
				object->v_field);
			}
			else if (data.objects->type == LIGHT)
			{
				t_light	*object = (t_light *)data.objects->object;
				printf("light\t:\t%.1f,%.1f,%.1f\t\t\t\t%.1f\t%d,%d,%d\n", object->cord.v_x, object->cord.v_y, object->cord.v_z, object->brightness, \
				object->clr.r, object->clr.g, object->clr.b);
			}
			else if (data.objects->type == LIGHTING)
			{
				t_lighting	*object = (t_lighting *)data.objects->object;
				printf("lighting:\t\t\t\t\t\t%.1f\t%d,%d,%d\n", object->ratio, object->clr.r, object->clr.g, object->clr.b);
			}
			data.objects = data.objects->next;
		}
	}

	t_mrt scean;
	t_ray ray;

	printf("%.1f\n", cam->normalized.v_z);
	scean.mlx = mlx_init();
	scean.mlx_win = mlx_new_window(scean.mlx, WIDTH, HEIGHT, "MINI_RT");
	scean.mlx_img = mlx_new_image(scean.mlx, WIDTH, HEIGHT);
	scean.mlx_add = mlx_get_data_addr(scean.mlx_img, &(scean.bit_per_px), &(scean.line_len), &(scean.endian));
	// puts("alo");
	draw(&scean, &ray, cam);
	mlx_loop(scean.mlx);
	return 0;
}
