/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:39:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/02 00:16:40 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	ft_memchr_ind(char *str, char c)
{
	int	count;

	if (!str)
		return (-1);
	count = 0;
	while (str[count])
	{
		if (str[count] == c)
			return (count);
		count++;
	}
	return (-1);
}

char	*ft_strfreejoin(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		count;

	count = -1;
	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (NULL);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (++count < s1_len)
		str[count] = s1[count];
	count = -1;
	while (++count + s1_len < s2_len + s1_len)
		str[s1_len + count] = s2[count];
	str[s1_len + s2_len] = 0;
	return (free(s1), str);
}
