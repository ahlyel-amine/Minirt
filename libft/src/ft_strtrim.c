/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:26:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/19 18:43:07 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	n;

	if (!s1)
		return (NULL);
	if (!set || !*set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	n = ft_strlen(s1);
	while (n && ft_strchr(set, *(s1 + n - 1)))
		n--;
	return (ft_substr(s1, 0, n));
}
