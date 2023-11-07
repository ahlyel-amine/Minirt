#ifndef MINIRT_H
# define MINIRT_H
#define WIDTH 1280
#define HEIGHT 820
#define FRAME 3
#define M_D 1.79769e+308
#define eps 1e-3
#include <stdbool.h>
#include "structs.h"

bool	parcer(char *scene, t_data	*data);

//--------------------intersection--------------------

bool	sphere_hit(t_ray *ray, t_sphere *sphere, t_hit_record *rec);
bool	plan_hit(t_ray *ray, t_plane *plan, t_hit_record *rec);
bool	cylinder_hit(t_ray *ray, t_cylender *cylinder, t_hit_record *rec);

//--------------------camera--------------------
t_vec	cam_to_world(double matrix[4][4], t_vec *dir);
void	lookat(t_mrt *rt, t_camera *cam);
void	Prime_ray(t_mrt *rt ,int x, int y, t_ray *ray,t_camera *cam);

#endif
