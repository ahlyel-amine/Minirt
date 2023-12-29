/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:39:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/12/29 19:45:29 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*hold;
	char		*line;
	char		*tmp;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (line);
	line = ft_read(fd);
	if (hold)
	{
		tmp = ft_strfreejoin(hold, line);
		free(line);
		line = tmp;
		hold = NULL;
	}
	if (line && ft_memchr_ind(line, '\n') != -1)
	{
		hold = ft_hold(line);
		line = ft_line(line);
	}
	return (line);
}

char	*ft_hold(char *line)
{
	char	*hold;
	size_t	i;
	int		j;

	i = -1;
	hold = NULL;
	while (line && line[++i])
		if (line[i] == '\n')
			break ;
	if (line && line[i] == '\n' && line[i + 1])
	{
		j = 0;
		hold = malloc((ft_strlen(line) - i + 2) * sizeof(char));
		if (!hold)
			return (NULL);
		while (line[i] && i++ < ft_strlen(line))
			hold[j++] = line[i];
		hold[j] = 0;
	}
	return (hold);
}

char	*ft_line(char *line)
{
	char	*tmp;
	int		i;
	int		count;

	i = -1;
	while (line[++i])
		if (line[i] == '\n')
			break ;
	if (line[i] == '\n' && line[i + 1])
	{
		tmp = malloc(i + 2);
		if (!tmp)
			return (NULL);
		count = -1;
		while (++count <= i)
			tmp[count] = line[count];
		tmp[count] = 0;
		free (line);
		line = tmp;
	}
	return (line);
}

char	*ft_read(int fd)
{
	char	*line;
	char	*tmp;
	int		count;

	line = NULL;
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	count = 1;
	while (ft_memchr_ind(line, '\n') == -1 && count)
	{
		count = read(fd, tmp, BUFFER_SIZE);
		if (count < 0)
			return (free(tmp), NULL);
		tmp[count] = 0;
		if (count)
		{
			line = ft_strfreejoin(line, tmp);
			if (!line)
				return (free(tmp), NULL);
		}
	}
	return (free(tmp), line);
}
