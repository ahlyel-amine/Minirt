/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:56:21 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/21 21:56:50 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "vector_bonus.h"

t_vec	create_vec_from_scalar(t_vec vec, double s)
{
	return ((t_vec){vec.v_x + s, vec.v_y + s, vec.v_z + s});
}

t_vec	at(double t, t_ray ray)
{
	return ((vec_addition(ray.origin, scalar_mult(ray.direction, t))));
}

double	distance(t_vec v, t_vec u)
{
	return (v_length(vec_sub(v, u)));
}

double	length(t_vec v)
{
	return (sqr(v.v_x) + sqr(v.v_y) + sqr(v.v_z));
}

double	v_length(t_vec v)
{
	return (sqrt(length(v)));
}
