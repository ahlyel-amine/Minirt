/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_on_vec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:53:30 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/27 16:02:56 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

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

