/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:03:01 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/11/28 15:57:07 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"
#include "library.h"
#include "vector.h"
#include "../../libft/include/libft.h"


bool	sphere_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_vec	oc;
	t_cord	p;
	double	discriminant;
	double	tmp;
	t_sphere *sphere = obj->object;
	oc = vec_sub(ray->origin, sphere->cord);
	p.a = dot_product(ray->direction, ray->direction);
	p.b = dot_product(oc, ray->direction);

	p.c = dot_product(oc, oc) - pow(sphere->diameter/2, 2);
	discriminant = p.b * p.b - (p.a * p.c);
	if (discriminant < eps)
		return (false);
	if (discriminant > eps)
	{
		tmp = (-p.b - sqrt(discriminant)) / (p.a);
		if (tmp <= eps || tmp >= M_D)
		{
			tmp = (-p.b + sqrt(discriminant)) / (p.a);
			if (tmp <= eps || tmp >= M_D)
				return (false);		
		}
	}else
	{
		tmp = -p.b / p.a;
		if (tmp <= eps || tmp >= M_D)
			return (false);
	}
	rec->t = tmp;
	rec->pHit = at(rec->t, *ray);
	t_vec norm = vec_sub(rec->pHit, sphere->cord);
	// if (dot_product(norm, norm) == 0.0)
	// 	return (false);
	rec->nHit = normalize(&norm);
	
	// printf("sphere clooor %d %d %d\n", sphere->clr.r, sphere->clr.g, sphere->clr.b);
	rec->h_color = create_vec((double)(sphere->clr.r) / 255, (double)(sphere->clr.g) / 255, (double)(sphere->clr.b) / 255);
	return (true);
}

bool	plan_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	double	denom;
	double	t;
	t_vec	p;
	t_plane *plan = obj->object;

	denom = dot_product(plan->normalized, ray->direction);
	if (fabs(denom) > eps)
	{
		p = vec_sub(plan->cord, ray->origin);
		t = dot_product(p, plan->normalized) / denom;
		if (t > eps)
		{
			rec->t = t;
			rec->pHit = at(rec->t, *ray);
			rec->nHit = plan->normalized;
			if (dot_product(rec->nHit, ray->direction) > 0)
				rec->nHit = vec_nega(rec->nHit);
			rec->h_color = create_vec((double)(plan->clr.r) / 255, (double)(plan->clr.g) / 255, (double)(plan->clr.b) / 255);
			return (true);
		}
	}
	return (false);
}
bool	solve_quad(t_ray *ray, t_cylender *cylinder, t_hit_record *rec)
{
	t_vec orthg;
	t_vec v;
	t_cord p;
	t_cord param;

	//pram.a => discriminant, param.b => solution 1, param.c => solution 2
	orthg = cross_product(ray->direction, cylinder->normalized);
	v = cross_product(vec_sub(ray->origin, cylinder->cord), cylinder->normalized);
	p.a = dot_product(orthg, orthg);
	p.b = 2 * dot_product(orthg, v);
	p.c = dot_product(v, v) - pow(cylinder->diameter * 0.5, 2);
	param.a = p.b * p.b -  4 * p.a * p.c;
	param.b = (-p.b - sqrt(param.a)) / (2 * p.a);
	param.c = (-p.b + sqrt(param.a)) / (2 * p.a);
	if (param.a <= eps || (param.b <= eps && param.c <= eps))
		return (false);
	if (param.b <= eps || (param.c > eps && (param.c < param.b)))
		param.b = param.c;
	return (rec->t = param.b, true);
	
}

void	calculate_disk_plan(t_cylender *cylinder, t_objects *obj, bool is_top)
{
	t_plane *plan;

	plan = obj->object;
	plan->normalized = cylinder->normalized;
	if (is_top)
		plan->cord = vec_addition(cylinder->cord, scalar_mult(cylinder->normalized, cylinder->height * 0.5));
	else
		plan->cord = vec_sub(cylinder->cord, scalar_mult(cylinder->normalized, cylinder->height * 0.5));
}

bool	cylinder_hit(t_ray *ray, t_cylender *cylinder, t_hit_record *rec)
{
	t_cord		p;
	t_vec		v;

	if (!solve_quad(ray, cylinder, rec))
		return false;
	rec->pHit = at(rec->t, *ray);
	v = vec_sub(rec->pHit, cylinder->cord);
	rec->nHit = normalized(cross_product(cross_product(v, cylinder->normalized), cylinder->normalized));
	if (dot_product(rec->nHit, ray->direction) > 0)
		rec->nHit = vec_nega(rec->nHit);
	if (pow(distance(cylinder->cord, rec->pHit), 2) > (pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2)))
		return false;
	rec->h_color = create_vec((double)(cylinder->clr.r) / 255, (double)(cylinder->clr.g) / 255, (double)(cylinder->clr.b) / 255);
	return true;
}

bool	f_cylinder_render(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_cylender	*cylinder;
	t_objects		*plan;

	rec->t = M_D;
	plan = malloc(sizeof(t_objects));
	plan->next = NULL;
	plan->object = malloc(sizeof(t_plane));
	ft_memset(plan->object, 0, sizeof(t_plane));
	t_hit_record	tmp_rec;
	cylinder = obj->object;
	calculate_disk_plan(cylinder, plan,true);
	((t_plane *)(plan->object))->clr = cylinder->clr;
	calculate_disk_plan(cylinder, plan, false);
	if (plan_hit(ray, plan, &tmp_rec)
		&& distance(tmp_rec.pHit, ((t_plane *)(plan->object))->cord) \
		<= ((cylinder->diameter * 0.5) - 0.002)
		&& rec->t > tmp_rec.t)
		*rec = tmp_rec;
	if (cylinder_hit(ray, cylinder, &tmp_rec)
		&& pow(distance(cylinder->cord, tmp_rec.pHit), 2) \
		<= pow(cylinder->height * 0.5, 2) + pow(cylinder->diameter * 0.5, 2))
		*rec = tmp_rec;
	return (rec->t < M_D && rec->t > eps);
}
void	tri_properties(t_triangle *triangle)
{
	triangle->edge0 = vec_sub(triangle->cord2, triangle->cord1);
	triangle->edge1 = vec_sub(triangle->cord3, triangle->cord2);
	triangle->edge2 = vec_sub(triangle->cord1, triangle->cord3);
	triangle->normalizer = cross_product(triangle->edge0, triangle->edge1);
	// normalize(&triangle->normalizer);
}

bool	check_tri_inter(t_hit_record *rec, t_triangle *tri)
{
	t_vec c1, c2, c3;
	c1 = vec_sub(rec->pHit, tri->cord1);
	c2 = vec_sub(rec->pHit, tri->cord2);
	c3 = vec_sub(rec->pHit, tri->cord3);
	if (dot_product(cross_product(tri->edge0, c1), tri->normalizer) > 0 &&
		dot_product(cross_product(tri->edge1, c2), tri->normalizer) > 0 &&
		dot_product(cross_product(tri->edge2, c3), tri->normalizer) > 0)
	{
		// rec->nHit = normalized(tri->normalizer);
		rec->h_color = create_vec((double)(tri->clr.r) / 255, (double)(tri->clr.g) / 255, (double)(tri->clr.b) / 255);
		return (true);
	}	
	return (false);
		
}
bool	triangle_hit(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_triangle	*triangle;
	double		dis;
	double 		dinom;

	triangle = (t_triangle *)obj->object;
	tri_properties(triangle);
	dinom = dot_product(ray->direction, triangle->normalizer);
	if (fabs(dinom) < eps)
		return (false);
	dis = -dot_product(triangle->normalizer, triangle->cord1);
	rec->t = -(dot_product(ray->origin, triangle->normalizer) + dis) / dinom;
	if (rec->t < eps)
		return (false);
	rec->pHit = at(rec->t, *ray);
	if (check_tri_inter(rec, triangle))
	{
		if (dot_product(rec->nHit, ray->direction) > 0)
			rec->nHit = vec_nega(rec->nHit);
		return (true);
	}
	return (false);
	// return (check_tri_inter(rec, triangle));
}


inter_func	intersect(int type)
{
	t_objects	*obj;
	inter_func 		obj_inter[4];
	obj_inter[SPHERE] = sphere_hit;
	obj_inter[PLANE] = plan_hit;
	obj_inter[CYLENDER] = f_cylinder_render;
	obj_inter[TRIANGLE] = triangle_hit;
	return (*(obj_inter + type));
}
t_vec	get_tex_color(t_texture_img *texture, double u, double v)
{
	int		x;
	int		y;
	int		index;
	t_vec	color;

	x = u * texture->width;
	y = (1 - v) * texture->height;
	index = (x * texture->bpp / 8) + (y * texture->line_len);
	color.v_x = (unsigned char)texture->addr[index + 2] / 255.0;
	color.v_y = (unsigned char)texture->addr[index + 1] / 255.0;
	color.v_z = (unsigned char)texture->addr[index + 0] / 255.0;
	return (color);
}

void	check_color(t_objects *object, t_hit_record *rec)
{
	double u;
	double v;
	if (object && object->textured)
	{
		get_uv_sphere(object->object, rec, &u, &v);
		rec->h_color = get_tex_color(((t_sphere *)(object->object))->texture, u, v);
	}
}
void	get_uv_sphere(t_sphere *sphere, t_hit_record *rec, double *u, double *v)
{
	t_vec unit_v;
	// Step 1: Calculate the unit vector from P to O
	unit_v = vec_sub(sphere->cord, rec->pHit);
	normalize(&unit_v);
	// Step 2: Calculate polar angle theta and azimuthal angle phi
	double theta = acos(unit_v.v_y);
	double phi = atan2(unit_v.v_x, unit_v.v_z);
	// Step 4: Map theta and phi to the range [0,1] to get UV coordinates
	*u = phi / (2 * M_PI);
	*v = theta / M_PI;
}

void	get_uv_plane(t_plane *plane, t_hit_record *rec, double *u, double *v)
{
	t_vec unit_v;
	
}
void	texture_bump_init(t_objects *shape, t_mrt *mrt)
{
	t_sphere	*sphere;
	t_cylender	*cylender;
	t_plane		*plane;
	t_triangle	*triangle;
	if (shape->type == SPHERE && shape->textured)
	{
		sphere = shape->object;
		sphere->texture->img = mlx_xpm_file_to_image(mrt->mlx, sphere->texture->path, &sphere->texture->width, &sphere->texture->height);
		if (!sphere->texture->img)
			sphere->texture->img = NULL;
		else
			sphere->texture->addr = mlx_get_data_addr(sphere->texture->img, &sphere->texture->bpp, &sphere->texture->line_len, &sphere->texture->endian);
	}
	else if (shape->type == CYLENDER && shape->textured)
	{
		cylender = shape->object;
		cylender->texture->img = mlx_xpm_file_to_image(mrt->mlx, cylender->texture->path, &cylender->texture->width, &cylender->texture->height);
		if (!cylender->texture->img)
			cylender->texture->img = NULL;
		else
			cylender->texture->addr = mlx_get_data_addr(cylender->texture->img, &cylender->texture->bpp, &cylender->texture->line_len, &cylender->texture->endian);
	}
	else if (shape->type == PLANE && shape->textured)
	{
		plane = shape->object;
		plane->texture->img = mlx_xpm_file_to_image(mrt->mlx, plane->texture->path, &plane->texture->width, &plane->texture->height);
		if (!plane->texture->img)
			plane->texture->img = NULL;
		else
			plane->texture->addr = mlx_get_data_addr(plane->texture->img, &plane->texture->bpp, &plane->texture->line_len, &plane->texture->endian);
	}
	else if (shape->type == TRIANGLE && shape->textured)
	{
		triangle = shape->object;
		triangle->texture->img = mlx_xpm_file_to_image(mrt->mlx, triangle->texture->path, &triangle->texture->width, &triangle->texture->height);
		if (!triangle->texture->img)
			triangle->texture->img = NULL;
		else
			triangle->texture->addr = mlx_get_data_addr(triangle->texture->img, &triangle->texture->bpp, &triangle->texture->line_len, &triangle->texture->endian);
	}
}

t_objects	*get_closes_object(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_objects	*object;
	double		closest_so_far;
	double		temp;
	t_hit_record	temp_rec;
	closest_so_far = M_D;
	object = NULL;

	while (obj)
	{
		if (intersect(obj->type)(ray, obj, &temp_rec) && temp_rec.t > eps && temp_rec.t < closest_so_far)
		{
			temp = temp_rec.t;
			if (temp < closest_so_far)
			{
				closest_so_far = temp;
				object = obj;
				*rec = temp_rec;
			}
		}
		obj = obj->next;
	}
	check_color(object, rec);
	return (object);
}

t_objects	*get_closes_object2(t_ray *ray, t_objects *obj, t_hit_record *rec)
{
	t_objects	*object;
	double		closest_so_far;
	double		temp;

	t_hit_record	temp_rec;
	closest_so_far = INFINITY;
	object = NULL;
	while (obj)
	{
		if (intersect(obj->type)(ray, obj, &temp_rec) && obj->type != PLANE)
		{
			temp = temp_rec.t;
			if (temp < closest_so_far)
			{
				closest_so_far = temp;
				object = obj;
				*rec = temp_rec;
				return obj;
			}
		}
		obj = obj->next;
	}
	return (object);
}

