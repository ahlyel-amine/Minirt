/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:16:23 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/12/14 18:21:17 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H
# include <stdbool.h>
# include <math.h>
# include "structs.h"

# define WIDTH 1920
# define HEIGHT 1080
# define FRAME 3
# define M_D 1.79769e+308
# define EPS 1e-3
# define MIN(X, Y)((X) < (Y) ? (X) : (Y))

typedef bool	(*object_parcer)(char *, t_data *);

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

# define MAX_OBJECTS	6

# define S_SPHERE	"sp"
# define S_CYLENDER	"cy"
# define S_PLANE		"pl"
# define S_LIGHTING	"A"
# define S_CAMERA	"C"
# define S_LIGHT		"L"
# define S_TRIANGLE	"tr"

#endif