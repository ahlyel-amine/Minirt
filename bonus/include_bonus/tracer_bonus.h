/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 21:54:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/17 21:58:02 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACER_BONUS_H
# define TRACER_BONUS_H

# include "structs_bonus.h"
# include <stdbool.h>

typedef bool	(*t_inter_func)(t_ray *, t_objects *, t_hit_record *);

t_objects		*get_closes_object(t_ray *ray, \
t_objects *obj, t_hit_record *rec);
t_objects		*get_first_close_object(t_ray *ray, \
t_objects *obj, t_hit_record *rec);
bool			sphere_hit(t_ray *ray, t_objects *obj, t_hit_record *rec);
bool			plan_hit(t_ray *ray, t_objects *obj, t_hit_record *rec);
bool			f_cylinder_render(t_ray *ray, \
t_objects *obj, t_hit_record *rec);
t_inter_func	intersect(int type);
void			prime_ray(int x, int y, t_ray *ray, t_camera *cam);
t_vec			raytrace(t_data *data, t_rays *rays, \
t_hit_record *rec, int level);

#endif