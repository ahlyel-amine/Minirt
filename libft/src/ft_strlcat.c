/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 03:03:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/02/19 18:42:47 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	returnlen;
	size_t	i;

	i = -1;
	returnlen = ft_strlen(src);
	if (!dstsize)
		return (returnlen);
	dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		return (returnlen + dstsize);
	returnlen += dstlen;
	while (*src && dstlen < dstsize - 1)
		*(dst + dstlen++) = *(src++);
	*(dst + dstlen) = '\0';
	return (returnlen);
}
