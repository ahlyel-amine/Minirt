/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_pattern_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:39:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/24 16:13:08 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <math.h>

void	checkread_borad(t_objects *obj, t_hit_record *rec)
{
	double		u;
	double		v;
	bool		checkred;
	t_features	spec;

	spec = get_specular_addr(obj);
	if (obj->type == PLANE)
	{
		get_uv_plane(obj->object, rec, &u, &u);
		checkred = true;
	}
	else if (obj->type == SPHERE)
	{
		get_uv_sphere(obj->object, rec, &u, &v);
		checkred = true;
	}
	else if (obj->type == CYLENDER)
	{
		get_uv_cylinder(obj->object, rec, &u, &v);
		checkred = true;
	}
	if (checkred && (int)(floor(spec.checkred_h * u) + \
	floor(spec.checkred_w * v)) % 2)
		rec->h_color = (t_vec){255, 255, 255};
}
