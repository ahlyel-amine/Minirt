#ifndef PARCER_H
# define PARCER_H

#include <stdbool.h>
#include "structs.h"

bool    cylender_parcer(char *line, t_data *data);
bool    plane_parcer(char *line, t_data *data);
bool    sphere_parcer(char *line, t_data *data);
bool    camera_parcer(char *line, t_data *data);
bool    light_parcer(char *line, t_data *data);
bool    lighting_parcer(char *line, t_data *data);
bool	cordinate_parcer(char **line, t_vec *cordinate, int marge_max, int marge_min);
bool	color_parcer(char *line, t_color *color);

#endif