/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:02:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/22 03:48:00 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_BONUS_H
# define LIBRARY_BONUS_H
# include <stdbool.h>
# include <math.h>
# include "structs_bonus.h"
# define WIDTH 1920	
# define HEIGHT 1080
# define FRAME 3
# define M_D 1.79769e+308
# define EPS 1e-3
# define min(X, Y)((X) < (Y) ? (X) : (Y))
# define REF_LEVEL 5

typedef bool	(*t_object_parcer)(char *, t_data *);
typedef void	(*t_texture_clear)(void *);
typedef void	(*t_obj_scale)(int, t_data *);
enum	e_types
{
	SPHERE		= 0x00,	
	CYLENDER	= 0x01,
	PLANE		= 0x02,
	TRIANGLE	= 0x03,
	CONE		= 0x04,
	LIGHTING	= 0x05,
	CAMERA		= 0x06,
	LIGHT		= 0x07,
	INVALID		= 0x20,
};

enum	e_size_types
{
	T_SPHERE		= sizeof(t_sphere),	
	T_CYLENDER		= sizeof(t_cylender),
	T_PLANE			= sizeof(t_plane),
	T_TRIANGLE		= sizeof(t_triangle),
	T_CONE			= sizeof(t_cone),
	T_LIGHTING		= sizeof(t_lighting),
	T_CAMERA		= sizeof(t_camera),
	T_LIGHT			= sizeof(t_light),
	T_INVALID		= 0,
};

# define MAX_OBJECTS	8

# define RT_FILE		".rt"

# define S_SPHERE		"sp"
# define S_CYLENDER		"cy"
# define S_PLANE		"pl"
# define S_LIGHTING		"A"
# define S_CAMERA		"C"
# define S_LIGHT		"l"
# define S_TRIANGLE		"tr"
# define S_CONE			"cn"

# define S_REF			"r="
# define S_SPEC			"s="
# define S_CHKBRD		"checkred="
# define S_XPM			".xpm\""
# define S_TXTR			"txtr=\""
# define S_ERR_TXTR		"txtr=\"E"
# define S_BUMP			"bump=\""
# define S_ERR_BUMP		"bump=\"E"
# define S_TRIANGLE		"tr"
# define S_CONE			"cn"

# define NAME			"MiniRT: "
# define ERR			"ERROR\n"
# define ERR_CN			"Cone : "
# define ERR_CY			"Cylender : "
# define ERR_PL			"Plane : "
# define ERR_SP			"Sphere : "
# define ERR_TR			"Triangle : "
# define ERR_A 			"Ambient lighting "
# define ERR_C 			"Camera "
# define ERR_L 			"Light "
# define ERR_N			"invalid normalized vector format\n"
# define ERR_CORD		"invalid cordinate format\n"
# define ERR_COLOR		"invalid color format\n"
# define ERR_VF			"vue field\n"
# define ERR_V			"invalid value "
# define ERR_F			"invalid format "
# define ERR_HA			"half angle "
# define ERR_DUP		"duplicate\n"
# define ERR_B			"brightness\n"
# define ERR_REF		"reflection\n"
# define ERR_SPEC		"Specular "
# define ERR_CHKBRD		"checkerboard "
# define ERR_DESC		"object/description\n"
# define ERR_SCN		"invalid scene file\n"
# define ERR_ESCN		"empty scene file\n"
# define ERR_INT		"intensity\n"
# define ERR_SHF		"shininess factor\n"
# define ERR_HT			"height "
# define ERR_WH			"width "
# define ERR_DR			"diameter "
# define ERR_MS			"missing "
# define ERR_TXTR		"texture/bump is only for objects : SPHERE/CYLENDER/PLANE\n"

#endif