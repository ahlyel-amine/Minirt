/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:59:59 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/27 16:02:29 by aahlyel          ###   ########.fr       */
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

t_vec	vec_nega(t_vec v)
{
	return ((t_vec){-v.v_x, -v.v_y, -v.v_z});
}
