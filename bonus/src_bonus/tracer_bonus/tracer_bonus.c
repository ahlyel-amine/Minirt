/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:03:33 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/18 17:23:12 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "minirt_bonus.h"
#include "tracer_bonus.h"
#include "draw_bonus.h"
#include "library_bonus.h"

void	loading_bar(double	percent)
{
	int lpad;
	int	rpad;

	lpad = (int)(percent * WBAR);
	rpad = WBAR - lpad;
	printf("\r[\033[32;1m%.*s%*s\033[0m] %.0f%%", (lpad), \
	PBAR, rpad,"", roundf(percent * 100));
	fflush(stdout);
}

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
			prime_ray(*(idx + 1), *idx, &(rays.ray), &ptr->data.camera);
			my_mlx_put(ptr->m_rt, *(idx + 1), *idx, \
			rgb_to_int(raytrace(&ptr->data, &rays, &rec, 10)));
			(*(idx + 1))++;
		}
		(*idx)++;
		pthread_mutex_lock(&(ptr->d->load));
		ptr->d->load_p += 1;
		loading_bar(((double)(ptr->d->load_p) / HEIGHT) / 5);
		pthread_mutex_unlock(&(ptr->d->load));
	}
	return (NULL);
}
