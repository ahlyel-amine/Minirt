/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:06:07 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/25 17:46:44 by aahlyel          ###   ########.fr       */
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
bool	features_parcer(char *line, t_features *obj, int type);
bool	cordinate_parcer(char **line, t_vec *cordinate, \
int marge_max, int marge_min);
int		color_parcer(char *line, t_color *color);
bool	check_reflection(char **line, double *reflection, bool *loop);
bool	check_specular(char **line, t_features *specular, bool *loop);
bool	check_checkerboard(char **line, t_features *checkred, \
bool *loop, int type);
bool	check_texture(char **line, char **texture, bool *loop, char *ind);
bool	get_path(char **line, char **texture);

#endif