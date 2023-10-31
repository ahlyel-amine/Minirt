/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 08:47:16 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/10/24 03:52:18 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "structs.h"
# include <math.h>
double	sqr(double x);
double	length(t_vec v);

t_vec	create_vec(double x, double y, double z);
t_vec	create_vec_from_scalar(double s);
double	v_length(t_vec v);
t_vec	normalize(t_vec *v);
t_vec	normalized(t_vec v);
double	dot_product(t_vec v, t_vec u);
t_vec	cross_product(t_vec v, t_vec u);
t_vec	vec_nega(t_vec v);
t_vec	vec_addition(t_vec v, t_vec u);
t_vec 	vec_sub(t_vec v, t_vec u);
t_vec	scalar_mult(t_vec v, double f);
t_vec	scalar_div(t_vec v, double f);
t_coord	at(double t, t_ray ray);

#endif