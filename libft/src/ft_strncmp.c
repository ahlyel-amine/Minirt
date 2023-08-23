/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:16:15 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/02 00:16:40 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (!*s1 && !*s2)
			return (0);
		s1++;
		s2++;
	}
	return (0);
}

int	ft_builtin_strncmp(char *s1, char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n--)
	{
		if (*s1 >= 'A' && *s1 <= 'Z')
			(*s1) += 32;
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (!*s1 && !*s2)
			return (0);
		s1++;
		s2++;
	}
	return (0);
}
