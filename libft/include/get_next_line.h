#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strfreejoin(char *s1, char *s2);
int		ft_memchr_ind(char *str, char c);
char	*ft_read(int fd);
char	*ft_line(char *line);
char	*ft_hold(char *line);

#endif
