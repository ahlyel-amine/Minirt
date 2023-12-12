/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:03:33 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/12 08:30:51 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "minirt_bonus.h"
#include "tracer_bonus.h"
#include "draw_bonus.h"
#include "library_bonus.h"

void	*draw(void *param)
{
	t_dataset		*ptr;
	t_hit_record	rec;
	t_rays			rays;
	int				idx[2];

	ptr = (t_dataset *)param;
	ft_memset(&rays, 0, sizeof(t_rays));
	*idx = ptr->s_y;
	while (*idx < ptr->e_y)
	{
		*(idx + 1) = ptr->s_x;
		while (*(idx + 1) < ptr->e_x)
		{
			Prime_ray(*(idx + 1), *idx, &(rays.ray), &ptr->data.camera);
			my_mlx_put(ptr->m_rt, *(idx + 1), *idx, \
			rgb_to_int(raytrace(&ptr->data, &rays, &rec, 10)));
			(*(idx + 1))++;
		}
		(*idx)++;
	}
	return (NULL);
}
