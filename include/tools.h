#ifndef TOOLS_H
#define TOOLS_H
#include "structs.h"
#include <stdbool.h>

int			skip_spaces(char *str);
void		get_integer(char **line, int *integer);
void		addobject_front(t_objects **lst, t_objects *new);
void    	addobject_back(t_objects **lst, t_objects *new);
double		ft_atod(char **ascii, bool *success, int marge_max, int marge_min);
t_objects	*newobject(void *object, unsigned char type);

#endif