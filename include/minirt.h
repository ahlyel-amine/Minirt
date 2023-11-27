/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:30:29 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/27 18:51:29 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
#define WIDTH 1920
#define HEIGHT 1080
#define FRAME 3
#define M_D 1.79769e+308
#define eps 1e-3
#include <stdbool.h>
#include "structs.h"
#define MIN(X, Y)((X) < (Y) ? (X) : (Y))

typedef bool	(*inter_func)(t_ray *, t_objects *, t_hit_record *);
bool	parcer(char *scene, t_data	*data);
void        draw(t_data data, t_mrt *scean);

//--------------------intersection--------------------



//--------------------camera--------------------
t_vec	cam_to_world(double matrix[4][4], t_vec *dir);
void	lookat(t_mrt *rt, t_camera *cam);


void print_vec(char *str, t_vec vec);
double distance(t_vec v, t_vec u);

t_light_effect	get_light_effect(t_data *data, t_rays *rays, t_objects *obj, t_hit_record *rec);
// t_vec	convert_light(int level, t_light_effect effect, t_objects *obj, t_specular_light refl);
// t_vec	convert_light(t_light_effect effect, t_objects *obj, t_specular_light refl);
// t_vec	convert_light(int level, t_light_effect effect, t_objects *obj);
t_vec	convert_light(t_light_effect effect, t_objects *obj);



void	print_scean(t_data data);

#endif
