/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:11:38 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/06 00:39:00 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "library_bonus.h"
#include "vector_bonus.h"

t_specular_light		get_specular_addr(t_objects *obj)
{
	if (obj->type == PLANE)
		return (((t_plane *)obj->object)->spec);
	else if (obj->type == SPHERE)
		return (((t_sphere *)obj->object)->spec);
	else if (obj->type == CYLENDER)
		return (((t_cylender *)obj->object)->spec);
	else
		return (((t_triangle *)obj->object)->spec);
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
	*u = (phi / (2 * M_PI)) * -1;
	*v = (theta / M_PI);
}

void	get_uv_plane(t_plane *plane, t_hit_record *rec, double *u, double *v)
{
	t_vec e1;
	t_vec e2;
	
	e1 = normalized(cross_product(plane->normalized, (t_vec){1, 0, 0}));
	if (e1.v_x == 0 && e1.v_y == 0 && e1.v_z == 0)
		e1 = normalized(cross_product(plane->normalized, (t_vec){0, 0, 1}));
	e2 = normalized(cross_product(plane->normalized, e1));
	*u = dot_product(e1, rec->pHit);
	*v = dot_product(e2, rec->pHit);
	
}
void get_uv_cylinder(t_cylender *cy, t_hit_record *rec, double *u, double *v)
{
    double theta;//azimuthal angle 
    double     r;// radius in the XZ plane
    double     h_z;//height along the z axis
    r = sqrt(rec->pHit.v_x * rec->pHit.v_x + rec->pHit.v_z * rec->pHit.v_z);
    theta = atan2(rec->pHit.v_z, rec->pHit.v_x);
    h_z = rec->pHit.v_y;
    *u = theta / (2 * M_PI);
	*v = h_z / cy->height;
}