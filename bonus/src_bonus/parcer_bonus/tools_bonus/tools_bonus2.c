/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:42:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/25 17:46:36 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "tools_bonus.h"

void	texutre_clear(t_objects *shape)
{
	t_features	*spec;

	spec = get_specular_add(shape);
	if (!spec)
		return ;
	if (spec->texture)
		free(spec->texture);
	if (shape->texture)
		free(shape->texture);
	if (spec->bump)
		free(spec->bump);
	if (shape->bump)
		free(shape->bump);
}

void	clear_texture(void *shape, int type)
{
	int	index;

	index = (type == SPHERE) * 1 + (type == PLANE) * 2 + (type == CYLENDER) * 3;
	if (index)
		texutre_clear(shape);
}
