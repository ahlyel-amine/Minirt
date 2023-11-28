/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:33:28 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/28 11:47:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include <stdlib.h>
#include "vector_bonus.h"
#include "minirt_bonus.h"
#include "library_bonus.h"

t_camera *create_cam(t_vec *origin, t_vec *direction, double fov)
{
	t_camera	*cam;
	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	return cam;
}

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
	t_vec	tmp;
	t_vec	forword;

	tmp = (t_vec){0, 1, 0};
	forword = cam->normalized;
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
