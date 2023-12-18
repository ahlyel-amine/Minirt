/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:30:29 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/28 11:10:44 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

#include <stdbool.h>
#include "structs_bonus.h"
#include "minirt_bonus.h"
# define PBAR "########################################"
# define WBAR 40
bool	parcer(char *scene, t_data	*data);
typedef bool	(*t_inter_func)(t_ray *, t_objects *, t_hit_record *);
typedef bool	(*t_texture)(void *, t_mrt *);

void	*draw(void *param);

//--------------------intersection--------------------

bool	sphere_hit(t_ray *ray, t_objects *obj, t_hit_record *rec);
bool	plan_hit(t_ray *ray, t_objects *obj, t_hit_record *rec);
bool	f_cylinder_render(t_ray *ray, t_objects *obj, t_hit_record *rec);
bool	triangle_hit(t_ray *ray, t_objects *obj, t_hit_record *rec);
bool	cone_hit(t_ray *ray, t_objects *obj, t_hit_record *rec);

t_inter_func	intersect(int type);

//--------------------camera--------------------
t_vec	cam_to_world(double matrix[4][4], t_vec *dir);
void	lookat(t_camera *cam);


void	print_scean(t_data data);
void print_vec(char *str, t_vec vec);
void	*draw(void *param);

t_objects	*get_closes_object(t_ray *ray, t_objects *obj, t_hit_record *rec);
t_objects	*get_closes_object2(t_ray *ray, t_objects *obj, t_hit_record *rec);
t_light_effect	get_light_effect(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec);
t_vec	convert_light(int level, t_light_effect effect, t_objects *obj, t_specular_light refl);
// t_vec	convert_light(t_light_effect effect, t_objects *obj, t_specular_light refl);
// t_vec	convert_light(int level, t_light_effect effect, t_objects *obj);
void	calculate_disk_plan(t_cylender *cylinder, t_objects *obj, bool is_top);

#endif
