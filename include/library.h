/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:16:23 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/29 10:04:32 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H
# include <stdbool.h>
# include <math.h>
# include "structs.h"

# define WIDTH 820
# define HEIGHT 680
# define FRAME 3
# define M_D 1.79769e+308
# define EPS 1e-3

typedef bool	(*t_object_parcer)(char *, t_data *);

enum	e_types
{
	SPHERE		= 0x00,
	CYLENDER	= 0x01,
	PLANE		= 0x02,
	LIGHTING	= 0x03,
	CAMERA		= 0x04,
	LIGHT		= 0x05,
	INVALID		= 0x20,
};

enum	e_size_types
{
	T_SPHERE		= sizeof(t_sphere),	
	T_CYLENDER		= sizeof(t_cylender),
	T_PLANE			= sizeof(t_plane),
	T_LIGHTING		= sizeof(t_lighting),
	T_CAMERA		= sizeof(t_camera),
	T_LIGHT			= sizeof(t_light),
	T_INVALID		= 0,
};

# define RT_FILE		".rt"

# define MAX_OBJECTS	6

# define S_SPHERE		"sp"
# define S_CYLENDER		"cy"
# define S_PLANE		"pl"
# define S_LIGHTING		"A"
# define S_CAMERA		"C"
# define S_LIGHT		"L"

# define ERR_CY_CORD 	"ERROR\nminirt: cylender invalid cordinate format"
# define ERR_CY_N 		"ERROR\nminirt: cylender invalid normalized format"
# define ERR_CY_DR 		"ERROR\nminirt: cylender invalid diameter format"
# define ERR_CY_HT 		"ERROR\nminirt: cylender invalid height format"
# define ERR_CY_COLOR 	"ERROR\nminirt: cylender invalid color format"

# define ERR_PL_CORD 	"ERROR\nminirt: plane invalid cordinate format"
# define ERR_PL_N 		"ERROR\nminirt: plane invalid normalized format"
# define ERR_PL_COLOR 	"ERROR\nminirt: plane invalid color format"

# define ERR_SP_CORD 	"ERROR\nminirt: sphere invalid cordinate format"
# define ERR_SP_DR 		"ERROR\nminirt: sphere invalid diameter format"
# define ERR_SP_COLOR 	"ERROR\nminirt: sphere invalid color format"

# define ERR_C_DUP	 	"ERROR\nminirt: camera duplicate information"
# define ERR_C_CORD	 	"ERROR\nminirt: camera invalid cordinate format"
# define ERR_C_N 		"ERROR\nminirt: camera invalid normalized format"
# define ERR_C_VF		"ERROR\nminirt: camera invalid vue field format"

# define ERR_L_DUP	 	"ERROR\nminirt: light duplicate information"
# define ERR_L_CORD	 	"ERROR\nminirt: light invalid cordinate format"
# define ERR_L_BR		"ERROR\nminirt: light invalid brightness format"
# define ERR_L_COLOR 	"ERROR\nminirt: light invalid color format"

# define ERR_A_DUP	 	"ERROR\nminirt: amnbient lighting duplicate information"
# define ERR_A_VL		"ERROR\nminirt: amnbient lighting invalid value"
# define ERR_A_COLOR 	"ERROR\nminirt: amnbient lighting invalid color format"

# define ERR_INVLD_O 	"ERROR\nminirt: invalid object/description format"

# define ERR_INVLD_SCN 	"ERROR\nminirt: invalid scene file"

# define ERR_EMPTY_SCN 	"ERROR\nminirt: empty scene file"

# define ERR_NO_L 		"ERROR\nminirt: missing light in scene"
# define ERR_NO_A 		"ERROR\nminirt: missing camera in scene"
# define ERR_NO_C 		"ERROR\nminirt: missing ambient lighting in scene"

#endif