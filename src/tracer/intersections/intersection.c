/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:03:01 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/17 22:04:36 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "library.h"
#include "tracer.h"
#include "vector.h"

t_objects	*get_closes_object(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_objects		*object;
	t_hit_record	temp_rec;
	double			closest_so_far;
	double			temp;

	closest_so_far = INFINITY;
	object = NULL;
	while (obj)
	{
		if (intersect(obj->type)(ray, obj, &temp_rec) && \
		temp_rec.t >EPS && temp_rec.t < closest_so_far)
		{
			temp = temp_rec.t;
			if (temp < closest_so_far)
			{
				closest_so_far = temp;
				object = obj;
				*rec = temp_rec;
			}
		}
		obj = obj->next;
	}
	return (object);
}

t_objects	*get_first_close_object(t_ray *ray, \
t_objects *obj, \
t_hit_record *rec)
{
	t_objects		*object;
	double			closest_so_far;
	double			temp;
	t_hit_record	temp_rec;

	object = NULL;
	closest_so_far = INFINITY;
	while (obj)
	{
		if (intersect(obj->type)(ray, obj, &temp_rec))
		{
			temp = temp_rec.t;
			if (temp < closest_so_far)
			{
				closest_so_far = temp;
				object = obj;
				*rec = temp_rec;
				return (obj);
			}
		}
		obj = obj->next;
	}
	return (object);
}

t_t_inter_func	intersect(int type)
{
	t_objects		*obj;
	t_t_inter_func	obj_inter[3];

	obj_inter[SPHERE] = sphere_hit;
	obj_inter[PLANE] = plan_hit;
	obj_inter[CYLENDER] = f_cylinder_render;
	return (*(obj_inter + type));
}
