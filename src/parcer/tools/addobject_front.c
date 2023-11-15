/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addobject_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:10:03 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/15 05:14:51 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	addobject_front(t_objects **lst, t_objects *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	addobject_back(t_objects **lst, t_objects *new)
{
	t_objects *tmp;

	tmp = *lst;
	if (new && lst)
	{
		if (!tmp)
		{
			*lst = new;
			return; 
		}
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
