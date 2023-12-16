#ifndef LIBRARY_H
#define LIBRARY_H
#include <stdbool.h>
# include <math.h>
#include "structs_bonus.h"
#define WIDTH 1920	
#define HEIGHT 1080
#define FRAME 3
#define M_D 1.79769e+308
#define eps 1e-3
#define MIN(X, Y)((X) < (Y) ? (X) : (Y))
#define REF_LEVEL 5
typedef	bool	(*object_parcer)(char *, t_data *);

enum	types
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

enum	size_types
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

#define	MAX_OBJECTS	8

#define	S_SPHERE	"sp"
#define	S_CYLENDER	"cy"
#define	S_PLANE		"pl"
#define	S_LIGHTING	"A"
#define	S_CAMERA	"C"
#define	S_LIGHT		"l"
#define	S_TRIANGLE	"tr"
#define	S_CONE		"cn"



# define S_NAME			"minirt: "
# define ERR			"ERROR\n"
# define ERR_CN			"cone : "
# define ERR_CY			"cylender : "
# define ERR_A 			"Ambient lighting "
# define ERR_C 			"Camera "
# define ERR_N			"invalid normalized vector format\n"
# define ERR_CORD		"invalid cordinate format\n"
# define ERR_COLOR		"invalid color format\n"
# define ERR_VFIELD		"field format "
# define ERR_VALUE		"invalid value "
# define ERR_HANGLE		"half angle "
# define ERR_DUP		"duplicate\n"
# define ERR_HEIGHT		"duplicate\n"
# define ERR_WIDTH		"height "
# define ERR_DIAMETER	"duplicate\n"




#endif