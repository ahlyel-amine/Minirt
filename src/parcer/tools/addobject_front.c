/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addobject_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:10:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/18 17:34:06 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "library.h"
#include "libft.h"
#include "tools.h"

void	addobject_front(t_objects **lst, t_objects *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

bool	object_validate(enum e_size_types size, enum e_types type, \
t_data *data, void *object)
{
	void		*new_object;
	t_objects	*s_object;

	new_object = ft_calloc(size, 1);
	if (!new_object)
		return (false);
	new_object = ft_memcpy(new_object, object, size);
	s_object = newobject(new_object, type);
	if (!s_object)
		return (free(new_object), false);
	addobject_front(&data->objects, s_object);
	return (true);
}
