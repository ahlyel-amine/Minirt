/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 03:03:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/24 17:42:01 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	returnlen;

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
