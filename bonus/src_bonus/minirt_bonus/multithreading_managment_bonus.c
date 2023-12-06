/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading_managment_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:40:30 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/06 00:58:13 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_bonus.h"
#include "libft.h"
#include "library_bonus.h"
#include "minirt_bonus.h"
#include "vector_bonus.h"
#include "draw_bonus.h"
#include <pthread.h>
#include <mlx.h>

void init_data_sets(t_dataset	*ptr, int *coef_x, int *coef_y, int i)
{
	ptr->s_x = ((*coef_x) * WIDTH / 50);
	ptr->e_x = (((*coef_x) + 1) * WIDTH / 50);
	ptr->s_y = ((*coef_y) * HEIGHT / 2);
	ptr->e_y = (((*coef_y) + 1) * HEIGHT / 2);
	if (i % 2)
	{
		(*coef_y) = 0;
		(*coef_x)++;
	}
	else
		(*coef_y)++;
}

void	join_threads(pthread_t	*th, int i)
{
	int a;

	a = 0;
	while (a < i)
		pthread_join(th[a++], NULL);
}

bool	make_threads(t_mrt *scean, t_data data)
{
	pthread_t	th[100];
	t_dataset	ptr[100];
	int 		coef_x;
	int 		coef_y;
	int 		i;

	i = -1;
	coef_x = 0;
	coef_y = 0;
	// print_scean(data);
	textures_binding(data.objects, scean);
	while (++i < 100)
	{
		ptr[i].m_rt = scean;
		ptr[i].data = data;
		init_data_sets(&ptr[i], &coef_x, &coef_y, i);
		if (pthread_create(&th[i], NULL, draw, &ptr[i]))
			return (join_threads(th,  i + 1), false);
	}
	join_threads(th, 100);
	return (true);
}
