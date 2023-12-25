/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addobject_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:10:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/25 17:46:19 by aahlyel          ###   ########.fr       */
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

void	features_bool(t_objects *object)
{
	t_features	ftrs;

	ftrs = get_specular_addr(object);
	if (ftrs.checkred_h > 0 || ftrs.checkred_w > 0)
		object->features.checkred = true;
	if (ftrs.reflection > 0)
		object->features.reflection = true;
	if (ftrs.intensity > 0 || ftrs.shininess_factor > 0)
		object->features.specular = true;
	if (ftrs.texture)
		object->features.texture = true;
	if (ftrs.bump)
		object->features.bump = true;
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
	features_bool(s_object);
	addobject_front(&data->objects, s_object);
	return (true);
}
