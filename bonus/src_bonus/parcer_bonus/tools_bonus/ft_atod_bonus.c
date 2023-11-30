/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:51:59 by aahlyel           #+#    #+#             */
/*   Updated: 2023/11/29 19:50:45 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "libft.h"
#include "tools_bonus.h"

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

#include "structs_bonus.h"
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

bool	ft_atod(char **ascii, double *result, int marge_max, int marge_min)
{
	int		digits_left;
	double	sign;
	
	*result = 0.0;
	sign = 1.0;
	digits_left = 0;
	*ascii += skip_spaces(*ascii);
	if ((*ascii)[0] == '-' && (*ascii)++)
		sign = -1.0;
	if (!ft_isdigit((*ascii)[0]) || !check_boundries(ascii, marge_max))
		return (false);
	*result = ft_datoi(ascii);
	if ((*ascii)[0] != '.' || !ft_isdigit((*ascii)[1])) 
		return (*result *= sign, true);
	(*ascii)++;
	while (ft_isdigit((*ascii)[digits_left]))
		digits_left++;
	if (!ft_isspace((*ascii)[digits_left]) && (*ascii)[digits_left] != ',')
		return (false);
	*result += (double)(ft_datoi(ascii) / pow(10.0, digits_left));
	*result *= sign;
	if (*result > (double)marge_max || *result < (double)marge_min)
		return (false);
	return (true);
}
