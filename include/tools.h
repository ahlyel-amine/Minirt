/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:34:17 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/18 15:59:00 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H
# include "structs.h"
# include <stdbool.h>
# include "library.h"

int			skip_spaces(char *str);
void		get_integer(char **line, int *integer);
void		addobject_front(t_objects **lst, t_objects *new);
bool		ft_atod(char **ascii, double *result, int marge_max, int marge_min);
t_objects	*newobject(void *object, unsigned char type);
void		clearobjs(t_objects **lst);
void		hooks_settings(t_data *data);
void		rotate(int key, t_data *data);
void		scale(int key, t_data *data);
void		cam_x(int key, t_data *data);
void		cam_y(int key, t_data *data);
bool		object_validate(enum e_size_types size, enum e_types type, \
t_data *data, void *object);

#endif