/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:33:28 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/08/26 08:27:56 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>
t_camera *create_cam(t_vec *origin, t_vec *direction, double fov)
{
	t_camera	*cam;
	cam = (t_camera *)malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	return cam;
}