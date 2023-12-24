/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:06:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/24 16:12:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_BONUS_H
# define TOOLS_BONUS_H

# include "structs_bonus.h"
# include "library_bonus.h"
# include <stdbool.h>

# define PKEY 35
# define CKEY 8
# define SKEY 1
# define JKEY 38
# define KKEY 40
# define LKEY 37
# define IKEY 34
# define ARROUP 126
# define ARRODOWN 125
# define ARROLEFT 123
# define ARRORIGHT 124
# define ZOOMIN 69
# define ZOOMOUT 78
# define KPLUS 24
# define KMIN 27
# define ESC 53

void				handle_bump(t_hit_record *rec, t_objects *obj);
void				get_integer(char **line, int *integer);
void				addobject_front(t_objects **lst, t_objects *new);
void				clearobjs(t_objects **lst);
void				clearlights(t_light **lst);
void				addlight(t_light **lst, t_light *new);
void				get_uv_sphere(t_sphere *sphere, t_hit_record *rec, \
double *u, double *v);
void				get_uv_plane(t_plane *plane, t_hit_record *rec, \
double *u, double *v);
void				get_uv_cylinder(t_cylender *cy, t_hit_record *rec, \
double *u, double *v);
int					skip_spaces(char *str);
bool				ft_atod(char **ascii, double *result, int marge_max, \
int marge_min);
bool				make_threads(t_mrt *scean, t_data data);
t_objects			*newobject(void *object, unsigned char type);
t_light				*newlight(t_light new);
t_features			get_specular_addr(t_objects *obj);
void				cam_y(int key, t_data *data);
void				cam_x(int key, t_data *data);
void				zoom(int key, t_data *data);
void				scale(int key, t_data *data);
void				rotate(int key, t_data *data);
void				hooks_settings(t_data *data);
void				skip(int key, t_data *data);
void				print_err(const int ac, ...);
void				clear_texture(void *shape, int type);
void				*bump_texture(t_sphere *sphere, t_mrt *img);
void				*bump_texture_p(t_plane *p, t_mrt *img);
bool				object_validate(enum e_size_types size, enum e_types type, \
t_data *data, void *object);
t_texture			texture_process(int type);
double				min(double a, double b);

#endif