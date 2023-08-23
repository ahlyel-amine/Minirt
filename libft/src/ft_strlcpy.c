/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 02:48:25 by aahlyel           #+#    #+#             */
/*   Updated: 2023/07/18 23:51:03 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	ls;

	ls = ft_strlen(src);
	if (dstsize == 0)
		return (ls);
	while (*src && --dstsize)
		*(dst++) = *(src++);
	*dst = '\0';
	return (ls);
}
