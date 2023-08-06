/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:28:57 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/19 18:42:34 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*(s++))
		if (*(s - 1) == (char)c)
			return ((char *)(s - 1));
	if (*(s - 1) == (char)c)
		return ((char *)(s - 1));
	return (NULL);
}
