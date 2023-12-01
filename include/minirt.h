/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:30:29 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/01 17:23:22 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdbool.h>
#include "structs.h"

bool	parcer(char *scene, t_data	*data);
void        draw(t_data data, t_mrt *scean);

//--------------------intersection--------------------



//--------------------camera--------------------
t_vec	cam_to_world(double matrix[4][4], t_vec *dir);
void	lookat(t_camera *cam);


void print_vec(char *str, t_vec vec);
double distance(t_vec v, t_vec u);

t_light_effect	get_light_effect(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec);
// t_vec	convert_light(int level, t_light_effect effect, t_objects *obj, t_specular_light refl);
// t_vec	convert_light(t_light_effect effect, t_objects *obj, t_specular_light refl);
// t_vec	convert_light(int level, t_light_effect effect, t_objects *obj);
t_vec	convert_light(t_light_effect effect, t_objects *obj);

void	print_scean(t_data data);

#endif
