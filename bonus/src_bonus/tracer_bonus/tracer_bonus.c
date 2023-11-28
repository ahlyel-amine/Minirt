/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:03:33 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/28 11:47:28 by aahlyel          ###   ########.fr       */
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

	ptr = (t_dataset *)param;
	ft_memset(&rays, 0, sizeof(t_rays));
	for (int j = ptr->s_y; j < ptr->e_y; j++)
	{
		for (int i = ptr->s_x; i < ptr->e_x; i++)
		{
			Prime_ray(ptr->m_rt, i, j, &(rays.ray), &ptr->data.camera);
			my_mlx_put(ptr->m_rt, i, j, rgb_to_int(raytrace(&ptr->data, &rays, &rec, 10)));
		}
	}
	return (NULL);
}
