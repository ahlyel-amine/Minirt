/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:49:37 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/15 10:00:28 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "structs.h"
#include "library.h"
#include "libft.h"

void	clearobjs(t_objects **lst)
{
	t_objects	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->type == CYLENDER)
			clearobjs(&(((t_cylender *)((*lst)->object))->p_face));
		free ((*lst)->object);
		free(*lst);
		*lst = tmp;
	}
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

void	get_integer(char **line, int *integer)
{
	int	i;
	
	i = 0;
	*line += skip_spaces(*line);
	while (ft_isdigit((*line)[i]))
		i++;
	*integer = ft_atoi((*line));
	*line += i;
}
