/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:47:51 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/14 11:54:11 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	chars_nbr(int n);

char	*ft_itoa(int n)
{
	char		*nbr;
	int			chr_count;
	long long	tmp;

	if (!n)
		return (ft_strdup("0"));
	chr_count = chars_nbr(n);
	nbr = (char *)ft_calloc(chr_count + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	tmp = n;
	if (tmp < 0)
		tmp = -tmp;
	while (chr_count && tmp)
	{
		*(nbr + --chr_count) = tmp % 10 + '0';
		tmp /= 10;
	}
	if (chr_count)
		*nbr = '-';
	return (nbr);
}

static size_t	chars_nbr(int n)
{
	size_t	s;

	s = 0;
	if (n < 0)
		s++;
	while (n != 0 && ++s)
		n /= 10;
	return (s);
}
