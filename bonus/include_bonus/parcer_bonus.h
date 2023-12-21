/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:06:07 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/22 00:51:07 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_BONUS_H
# define PARCER_BONUS_H

# include <stdbool.h>
# include "structs_bonus.h"

bool	cylender_parcer(char *line, t_data *data);
bool	plane_parcer(char *line, t_data *data);
bool	sphere_parcer(char *line, t_data *data);
bool	camera_parcer(char *line, t_data *data);
bool	light_parcer(char *line, t_data *data);
bool	lighting_parcer(char *line, t_data *data);
bool	triangle_parcer(char *line, t_data *data);
bool	cone_parcer(char *line, t_data *data);
bool	check_for_features(char *line, t_specular_light *spec, int type);

bool	cordinate_parcer(char **line, t_vec *cordinate, \
int marge_max, int marge_min);
int		color_parcer(char *line, t_color *color);

#endif