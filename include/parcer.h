/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:24:38 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/14 18:25:50 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H

# include <stdbool.h>
# include "structs.h"

bool	cylender_parcer(char *line, t_data *data);
bool	plane_parcer(char *line, t_data *data);
bool	sphere_parcer(char *line, t_data *data);
bool	camera_parcer(char *line, t_data *data);
bool	light_parcer(char *line, t_data *data);
bool	lighting_parcer(char *line, t_data *data);
bool	cordinate_parcer(char **line, t_vec *cordinate, \
int marge_max, int marge_min);
bool	color_parcer(char *line, t_color *color);

#endif