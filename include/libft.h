/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:24:21 by aahlyel           #+#    #+#             */
/*   Updated: 2023/08/01 19:43:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

size_t		ft_strlen(const char *s);
void		ft_putendl_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
int			ft_isspace(int c);
char		**ft_split(char const *s, char c);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
double		ft_atod(char **ascii, bool *success, int marge_max, int marge_min);
t_objects	*newobject(void *object, unsigned char type);
void		addobject_front(t_objects **lst, t_objects *new);

#endif
