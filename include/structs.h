#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
typedef struct s_cord
{
	double	a;
	double	b;
	double	c;
}	t_cord;

typedef struct s_vec
{
	double	v_x;
	double	v_y;
	double	v_z;
}	t_vec;


typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

// typedef t_cord	(*param_at)(double t, t_ray ray);
# define t_coord t_vec
typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_lighting
{
	t_color	clr;
	double	ratio;
}	t_lighting;

typedef struct s_camera
{
	unsigned char	v_field;
	t_vec			cord;
	t_vec			normalized;
	t_vec			up;
	t_vec			right;
	double			scale;
	double			aspect_ratio;
}	t_camera;

typedef struct s_light
{
	t_color	clr;
	double	brightness;
	t_vec	cord;
	struct s_light	*next;
}	t_light;

typedef struct s_plane
{
	t_color	clr;
	t_vec	cord;
	t_vec	normalized;
}	t_plane;

typedef struct s_cylender
{
	t_color	clr;
	double	diameter;
	double	height;
	t_vec	cord;
	t_vec	normalized;
}	t_cylender;

typedef struct s_sphere
{
	t_color	clr;
	double	diameter;
	t_vec	cord;
}	t_sphere;

typedef	struct s_object
{
	unsigned char	type;
	void			*object;
	struct s_object	*next;
}	t_objects;

typedef struct s_counter
{
	int sphere;
	int cylender;
	int plane;
}	t_counter;

typedef	struct s_data
{
	t_objects	*objects;
	t_lighting	lighting;
	t_light		*light;
	t_counter	counter;
	t_camera	camera;
}	t_data;

typedef struct s_mrt
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	char	*mlx_add;
	int		bit_per_px;
	int		line_len;
	int		endian;
	double	cam_matrix[4][4];
}	t_mrt;

typedef struct s_hit_record
{
	double	t;
	t_vec	pHit;
	t_vec	nHit;
	t_vec 	h_color;	
}	t_hit_record;

typedef struct s_light_effect
{
	t_vec	ambient;
	t_vec	diffuse;
	t_vec	specular;
	t_vec	reflect;
}	t_light_effect;

typedef struct s_rays
{
	t_ray	ray;
	t_ray	shadow_ray;
	t_objects	*closet_obj;
}	t_rays;

typedef struct s_dataset
{
	t_mrt *m_rt;
	t_data data;
	int s_x;
	int s_y;
	int e_x;
	int e_y;
}	t_dataset;

// typedef enum e_bool
// {
// 	false,
// 	true
// }	t_bool;

#endif