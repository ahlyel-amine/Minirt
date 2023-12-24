/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:49:37 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/24 16:56:29 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdarg.h>
#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"

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
		clear_texture((*lst)->object, (*lst)->type);
		free ((*lst)->object);
		free(*lst);
		*lst = tmp;
	}
}

void	clearlights(t_light **lst)
{
	t_light	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
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

void	print_err(const int ac, ...)
{
	va_list	args;
	int		tmp;

	tmp = ac;
	va_start(args, ac);
	while (tmp--)
		ft_putstr_fd(va_arg(args, char *), 2);
	va_end(args);
}
