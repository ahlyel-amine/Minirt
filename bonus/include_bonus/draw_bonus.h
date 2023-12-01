#ifndef DRAW_H
#define DRAW_H

void	color_range_norm(t_vec *color);
t_vec	raytrace(t_data *data, t_rays *rays, t_hit_record *rec, int level);
void	my_mlx_put(t_mrt *rt, int x, int y, int color);
int	    get_pixel(t_mrt *rt, int x, int y);
int	    rgb_to_int(t_coord color);
void	Prime_ray(int x, int y, t_ray *ray,t_camera *cam);
t_vec	c_color(t_vec f_c, t_vec s_c, double p1, double p2);
int 	rgb_to_int(t_coord color);
t_vec   merge_light(t_vec color, t_color light_color, double ratio);
bool    shadow_ray(t_rays *rays, t_light *light, t_objects *obj, t_hit_record *rec);
t_vec	specular_light(t_rays *rays, t_light *light, t_specular_light speclr, t_hit_record *rec);
t_vec	diffuse_effect(t_rays *rays, t_light *light, t_hit_record *rec);
void	nineties(t_vec *color);
t_vec	checkread_borad(t_vec color, t_vec p, t_hit_record *obj);

#endif