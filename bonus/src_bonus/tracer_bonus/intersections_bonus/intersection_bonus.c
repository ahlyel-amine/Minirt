/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:03:01 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/24 16:58:39 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "structs_bonus.h"
#include "library_bonus.h"
#include "tracer_bonus.h"
#include "draw_bonus.h"

t_objects	*get_closes_object(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_objects		*object;
	t_hit_record	temp_rec;
	double			closest_so_far;

	closest_so_far = M_D;
	object = NULL;
	while (obj)
	{
		if (intersect(obj->type)(ray, obj, &temp_rec) && \
		temp_rec.t > EPS && temp_rec.t < closest_so_far)
		{
			if (temp_rec.t < closest_so_far)
			{
				closest_so_far = temp_rec.t;
				object = obj;
				*rec = temp_rec;
			}
		}
		obj = obj->next;
	}
	check_color(object, rec);
	return (object);
}

t_inter_func	intersect(int type)
{
	static t_inter_func	obj_inter[5];
	static bool			init;

	if (!init)
	{
		init = true;
		obj_inter[SPHERE] = sphere_hit;
		obj_inter[PLANE] = plan_hit;
		obj_inter[CYLENDER] = f_cylinder_render;
		obj_inter[TRIANGLE] = triangle_hit;
		obj_inter[CONE] = cone_hit;
	}
	return (*(obj_inter + type));
}
