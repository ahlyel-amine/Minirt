/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:33:28 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/02 13:21:37 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>
#include "vector.h"
#include "minirt.h"

t_camera *create_cam(t_vec *origin, t_vec *direction, double fov)
{
	t_camera	*cam;
	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	return cam;
}
// t_vector	bump_normal(t_shape s, t_vector n, t_vector eye, t_point p)
// {
// 	int			c[2];
// 	int			x[2];
// 	int			y[2];
// 	double		b_scale[2];
// 	t_tools		b;

// 	b.t = s.bump_img;
// 	b.uv = s.mapping.uv_map(mul_mat_point(s.ivers_tran, p));
// 	x[0] = b.uv.u * (b.t->width - 1);
// 	y[0] = (1 - b.uv.v) * (b.t->height - 1);
// 	y[1] = (y[0] + 1) % b.t->height;
// 	x[1] = (x[0] + 1) % b.t->width;
// 	c[0] = ((int *)b.t->pixels)[x[0] + y[0] * b.t->width] & 255;
// 	c[1] = ((int *)b.t->pixels)[x[0] + y[1] * b.t->width] & 255;
// 	b_scale[0] = ((double)c[1] - c[0]) / 9;
// 	c[1] = ((int *)b.t->pixels)[x[1] + y[0] * b.t->width] & 255;
// 	b_scale[1] = ((double)c[1] - c[0]) / 9;
// 	b.pu = cross_product(n, eye);
// 	b.pv = cross_product(n, b.pu);
// 	b.n_ = n;
// 	b.n_ = add_to_vector(b.n_, scaler_vect(cross_product(b.pu, n), b_scale[1]));
// 	b.n_ = add_to_vector(b.n_, scaler_vect(cross_product(b.pv, n), b_scale[0]));
// 	return (normalize(b.n_));
// }
t_vec	cam_to_world(double matrix[4][4], t_vec *dir)
{
	t_vec	v;	
	v.v_x = dir->v_x * matrix[0][0] + dir->v_y * matrix[1][0] + dir->v_z * matrix[2][0];
	v.v_y = dir->v_x * matrix[0][1] + dir->v_y * matrix[1][1] + dir->v_z * matrix[2][1];
	v.v_z = dir->v_x * matrix[0][2] + dir->v_y * matrix[1][2] + dir->v_z * matrix[2][2];
	return v;
}

void	lookat(t_mrt *rt, t_camera *cam)
{
	t_vec	tmp = {0, 1, 0};
	t_vec	forword = cam->normalized;
	cam->right = cross_product(tmp, forword);
	cam->up = cross_product(forword, cam->right);
	rt->cam_matrix[0][0] = cam->right.v_x;
	rt->cam_matrix[0][1] = cam->right.v_y;
	rt->cam_matrix[0][2] = cam->right.v_z;
	rt->cam_matrix[1][0] = cam->up.v_x;
	rt->cam_matrix[1][1] = cam->up.v_y;
	rt->cam_matrix[1][2] = cam->up.v_z;
	rt->cam_matrix[2][0] = forword.v_x;
	rt->cam_matrix[2][1] = forword.v_y;
	rt->cam_matrix[2][2] = forword.v_z;
	cam->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	cam->scale = tan(((double)cam->v_field / 2) * M_PI / 180);
}

