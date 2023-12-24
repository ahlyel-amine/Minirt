/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:11:38 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/24 17:02:44 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "library_bonus.h"
#include "vector_bonus.h"
#include <stdlib.h>

t_features	get_specular_addr(t_objects *obj)
{
	if (obj->type == PLANE)
		return (((t_plane *)obj->object)->spec);
	else if (obj->type == SPHERE)
		return (((t_sphere *)obj->object)->spec);
	else if (obj->type == CYLENDER)
		return (((t_cylender *)obj->object)->spec);
	else if (obj->type == TRIANGLE)
		return (((t_triangle *)obj->object)->spec);
	else
		return (((t_cone *)obj->object)->spec);
}

void	get_uv_sphere(t_sphere *sphere, t_hit_record *rec, \
double *u, double *v)
{
	t_vec	unit_v;
	double	theta;
	double	phi;

	unit_v = vec_sub(sphere->cord, rec->p_hit);
	normalize(&unit_v);
	theta = acos(unit_v.v_y);
	phi = atan2(unit_v.v_x, unit_v.v_z);
	*u = -((phi) / (2 * M_PI)) + (sphere->rot_x);
	*v = ((theta) / M_PI);
}

void	get_uv_plane(t_plane *plane, t_hit_record *rec, \
double *u, double *v)
{
	t_vec	e1;
	t_vec	e2;

	e1 = normalized(cross_product(plane->normalized, (t_vec){1, 0, 0}));
	if (e1.v_x == 0 && e1.v_y == 0 && e1.v_z == 0)
		e1 = normalized(cross_product(plane->normalized, (t_vec){0, 0, 1}));
	e2 = normalized(cross_product(plane->normalized, e1));
	*u = dot_product(e1, rec->p_hit);
	*v = dot_product(e2, rec->p_hit);
}

void	get_uv_cylinder(t_cylender *cy, t_hit_record *rec, double *u, double *v)
{
	double	theta;
	double	h_z;
	// double	r;
// r = sqrt(rec->p_hit.v_x * rec->p_hit.v_x + rec->p_hit.v_z * rec->p_hit.v_z);
	theta = atan2(rec->p_hit.v_z, rec->p_hit.v_x);
	h_z = rec->p_hit.v_y;
	*u = theta / (2 * M_PI);
	*v = h_z / cy->height;
}

void	skip(int key, t_data *data)
{
	(void)key;
	(void)data;
}
