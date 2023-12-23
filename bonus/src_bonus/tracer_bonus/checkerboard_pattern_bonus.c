/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_pattern_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:39:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/23 15:46:31 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include <math.h>

void	checkread_borad(t_objects *obj, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double	d;
	bool	checkred;

	if (obj->type == PLANE && obj->features.checkred == true)
	{
		c = ((t_plane *)obj->object)->spec.checkred_h;
		d = ((t_plane *)obj->object)->spec.checkred_w;
		get_uv_plane(obj->object, rec, &a, &b);
		checkred = true;
	}
	else if (obj->type == SPHERE && obj->features.checkred == true)
	{
		c = ((t_sphere *)obj->object)->spec.checkred_h;
		d = ((t_sphere *)obj->object)->spec.checkred_w;
		get_uv_sphere(obj->object, rec, &a, &b);
		checkred = true;
	}
	else if (obj->type == CYLENDER && obj->features.checkred == true)
	{
		c = ((t_cylender *)obj->object)->spec.checkred_h;
		d = ((t_cylender *)obj->object)->spec.checkred_w;
		get_uv_cylinder(obj->object, rec, &a, &b);
		checkred = true;
	}
	if (checkred && (int)(floor(c * a) + floor(d * b)) % 2)
		rec->h_color = (t_vec){255, 255, 255};
}
