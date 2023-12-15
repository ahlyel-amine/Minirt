#ifndef TOOLS_H
#define TOOLS_H

#include "structs_bonus.h"
#include "library_bonus.h"
#include <stdbool.h>

void				handle_bump(t_hit_record *rec, t_objects *obj);
void				get_integer(char **line, int *integer);
void				addobject_front(t_objects **lst, t_objects *new);
void				clearobjs(t_objects **lst);
void				clearlights(t_light **lst);
void				addlight(t_light **lst, t_light *new);
void				get_uv_sphere(t_sphere *sphere, t_hit_record *rec, double *u, double *v);
void				get_uv_plane(t_plane *plane, t_hit_record *rec, double *u, double *v);
void				get_uv_cylinder(t_cylender *cy, t_hit_record *rec, double *u, double *v);
int					skip_spaces(char *str);
bool				ft_atod(char **ascii, double *result, int marge_max, int marge_min);
bool				make_threads(t_mrt *scean, t_data data);
double				get_greyscale_texture_c(t_texture_img *bump, int x, int y);
t_objects			*newobject(void *object, unsigned char type);
t_light				*newlight(t_light new);
t_specular_light	get_specular_addr(t_objects *obj);
void				cam_y(int key, t_data *data);
void				cam_x(int key, t_data *data);
void				scale(int key, t_data *data);
void				rotate(int key, t_data *data);
void				hooks_settings(t_data *data);
void				skip(int key, t_data *data);
void				ft_putendl_fd_arg(const int ac, ...);
bool	            object_validate(enum size_types size, enum types type, t_data *data, void *object);

#endif