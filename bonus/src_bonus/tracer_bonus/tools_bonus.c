/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:11:38 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 12:09:40 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "library_bonus.h"

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
