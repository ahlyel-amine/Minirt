#ifndef TOOLS_H
#define TOOLS_H
#include "structs_bonus.h"
#include <stdbool.h>

int			skip_spaces(char *str);
void		get_integer(char **line, int *integer);
void		addobject_front(t_objects **lst, t_objects *new);
void    	addobject_back(t_objects **lst, t_objects *new);
bool    	ft_atod(char **ascii, double *result, int marge_max, int marge_min);
t_objects	*newobject(void *object, unsigned char type);
bool    	make_threads(t_mrt *scean, t_data data);
void	    clearobjs(t_objects **lst);
void		clearlights(t_light **lst);
t_light 	*newlight(t_light new);
void					addlight(t_light **lst, t_light *new);
t_specular_light		get_specular_addr(t_objects *obj);
void					get_uv_sphere(t_sphere *sphere, t_hit_record *rec, double *u, double *v);
void					get_uv_plane(t_plane *plane, t_hit_record *rec, double *u, double *v);
void                    get_uv_cylinder(t_cylender *cy, t_hit_record *rec, double *u, double *v);

#endif