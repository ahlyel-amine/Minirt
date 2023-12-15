/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:57:21 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 11:47:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "vector_bonus.h"

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
