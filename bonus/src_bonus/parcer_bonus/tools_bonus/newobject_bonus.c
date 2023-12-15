/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newobject.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:58:35 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 11:47:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include <stdlib.h>

t_objects	*newobject(void *object, unsigned char type)
{
	t_objects	*node;

	node = (t_objects *)malloc(sizeof(t_objects));
	if (node)
	{
		node->type = type;
		node->object = object;
		node->next = NULL;
	}
	return (node);
}

t_light	*newlight(t_light new)
{
	t_light	*light;
	
	light = malloc(sizeof(t_light));
	if (light)
	{
		light->brightness = new.brightness;
		light->clr = new.clr;
		light->cord = new.cord;
		light->next = NULL;
	}
	return (light);
}