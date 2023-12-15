/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_pattern_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:39:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/14 18:33:43 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "vector_bonus.h"
#include <math.h>

t_vec	checkread_borad(t_vec color, t_vec p, t_hit_record *obj)
{
	if (dot_product(obj->n_hit, (t_vec){0, 0, 1}))
		if ((int)(floor(p.v_x) + floor(p.v_y)) % 2)
			return ((t_vec){255, 255, 255});
	if (dot_product(obj->n_hit, (t_vec){0, 1, 0}))
		if ((int)(floor(p.v_x) + floor(p.v_z)) % 2)
			return ((t_vec){255, 255, 255});
	if (dot_product(obj->n_hit, (t_vec){1, 0, 0}))
		if ((int)(floor(p.v_y) + floor(p.v_z)) % 2)
			return ((t_vec){255, 255, 255});
	return (color);
}
