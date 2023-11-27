#ifndef LIBRARY_H
#define LIBRARY_H
#include <stdbool.h>
# include <math.h>
#include "structs.h"

typedef	bool	(*object_parcer)(char *, t_data *);

enum	types
{
	SPHERE		= 0x00,
	CYLENDER	= 0x01,
	PLANE		= 0x02,
	LIGHTING	= 0x03,
	CAMERA		= 0x04,
	LIGHT		= 0x05,
	INVALID		= 0x20,
};


#define	MAX_OBJECTS	6

#define	S_SPHERE	"sp"
#define	S_CYLENDER	"cy"
#define	S_PLANE		"pl"
#define	S_LIGHTING	"A"
#define	S_CAMERA	"C"
#define	S_LIGHT		"L"
#define	S_TRIANGLE	"tr"

#endif