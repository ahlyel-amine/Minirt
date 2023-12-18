/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:36:59 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/18 15:58:23 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACER_H
# define TRACER_H

# include "structs.h"

typedef bool	(*t_inter_func)(t_ray *, t_objects *, t_hit_record *);

t_inter_func	intersect(int type);
t_objects		*get_closes_object(t_ray *ray, t_objects *obj, \
t_hit_record *rec);
t_vec			raytrace(t_data *data, t_rays *rays, t_hit_record *rec);
bool			sphere_hit(t_ray *ray, t_objects *obj, t_hit_record *rec);
bool			plan_hit(t_ray *ray, t_objects *obj, t_hit_record *rec);
bool			f_cylinder_render(t_ray *ray, t_objects *obj, \
t_hit_record *rec);
void			prime_ray(int x, int y, t_ray *ray, t_camera *cam);

#endif