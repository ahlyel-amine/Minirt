/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newobject.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:58:35 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/02 00:16:40 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

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
