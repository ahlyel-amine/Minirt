/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:51:59 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/05 01:30:04 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "libft.h"
#include "tools.h"

static int	ft_datoi(char **str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	if (**str == '-' || **str == '+')
		if (*((*str)++) == '-')
			sign = -1;
	while (**str && ft_isdigit(**str))
		res = (res * 10) + *((*str)++) - '0';
	return ((int)(res * sign));
}

#include "structs.h"
bool	check_boundries(char **ascii, int marge)
{
	int i;

	i = 0;
	while (ft_isdigit((*ascii)[i]))
	{
		if (marge < 10 && marge < (*ascii)[i] - 48)
			return (false);
		marge /= 10;
		i++;
	}
	return (true);
}

double	ft_atod(char **ascii, bool *success, int marge_max, int marge_min)
{
	int		digits_left;
	double	result;
	double	sign;
	
	result = 0.0;
	sign = 1.0;
	digits_left = 0;
	*ascii += skip_spaces(*ascii);
	if ((*ascii)[0] == '-' && (*ascii)++)
		sign = -1.0;
	if (!ft_isdigit((*ascii)[0]) || !check_boundries(ascii, marge_max))
		return (*success = false, 0);
	result = ft_datoi(ascii);
	if ((*ascii)[0] != '.' || !ft_isdigit((*ascii)[1]))
		return (*success = false, 0);
	(*ascii)++;
	while (ft_isdigit((*ascii)[digits_left]))
		digits_left++;
	if (!ft_isspace((*ascii)[digits_left]) && (*ascii)[digits_left] != ',')
		return (*success = false, 0);
	result += (double)(ft_datoi(ascii) / pow(10.0, digits_left));
	result *= sign;
	if (result > (double)marge_max || result < (double)marge_min)
		return (*success = false, 0);
	return (result);
}
