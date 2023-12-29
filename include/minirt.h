/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:30:29 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/29 20:58:32 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include "structs.h"

bool			parcer(char *scene, t_data	*data);
void			draw(t_data data, t_mrt *scean);

//--------------------camera--------------------
t_vec			cam_to_world(double matrix[4][4], t_vec *dir);
void			lookat(t_camera *cam);

void			print_vec(char *str, t_vec vec);
double			distance(t_vec v, t_vec u);

t_light_effect	get_light_effect(t_data *data, t_rays *rays, t_hit_record *rec);
t_vec			convert_light(t_light_effect effect);

void			calculate_disk_plan(t_cylender *cylinder, \
t_objects *obj, bool is_top);

#endif
