/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addobject_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:10:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/15 22:27:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "library_bonus.h"
#include "tools_bonus.h"
#include "libft.h"

void	addobject_front(t_objects **lst, t_objects *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	addlight(t_light **lst, t_light *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

bool	object_validate(enum size_types size, enum types type, t_data *data, void *object)
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