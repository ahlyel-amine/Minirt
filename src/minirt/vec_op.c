/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:56:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/07 17:19:54 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <math.h>

double	sqr(double x)
{
	return (x * x);
}

t_vec	create_vec(double x, double y, double z)
{
	return ((t_vec){x, y, z});
}

t_vec	create_vec_from_scalar(double s)
{
	return ((t_vec){s, s, s});
}

double	length(t_vec v)
{
	return (sqr(v.v_x) + sqr(v.v_y) + sqr(v.v_z));
}

double	v_length(t_vec v)
{
	return (sqrt(length(v)));
}
// change a vector to have a lenght of 1
t_vec	normalize(t_vec *v)
{
	double	len;

	len = 1.0 / v_length(*v);
	v->v_x *= len;
	v->v_y *= len;
	v->v_z *= len;
	return (*v); 
}

t_vec	normalized(t_vec v)
{
	t_vec	res;

	res = v;
	return (normalize(&res));
}

double	dot_product(t_vec v, t_vec u)
{
	return (v.v_x * u.v_x + v.v_y * u.v_y + v.v_z * u.v_z);
}

t_vec	cross_product(t_vec v, t_vec u)
{
	t_vec	res;

	res.v_x = v.v_y * u.v_z - v.v_z * u.v_y;
	res.v_y = v.v_z * u.v_x - v.v_x * u.v_z;
	res.v_z = v.v_x * u.v_y - v.v_y * u.v_x;
	return (res);
}

t_vec	vec_nega(t_vec v)
{
	return ((t_vec){-v.v_x, -v.v_y, -v.v_z});
}

t_vec vec_addition(t_vec v, t_vec u)
{
	return ((t_vec){v.v_x + u.v_x, v.v_y + u.v_y, v.v_z + u.v_z});
}

t_vec vec_sub(t_vec v, t_vec u)
{
	return ((t_vec){v.v_x - u.v_x, v.v_y - u.v_y, v.v_z - u.v_z});
}

t_vec	scalar_mult(t_vec v, double f)
{
	return ((t_vec){v.v_x * f, v.v_y * f, v.v_z * f});
}

t_vec	scalar_div(t_vec v, double f)
{
	return ((t_vec){v.v_x / f, v.v_y / f, v.v_z / f});
}

t_coord	at(double t, t_ray ray)
{
	return ((vec_addition(ray.origin, scalar_mult(ray.direction, t))));
}