SRC			= src/ft_atoi.c\
              src/ft_bzero.c\
              src/ft_calloc.c\
              src/ft_isalnum.c\
              src/ft_isalpha.c\
              src/ft_isascii.c\
              src/ft_isdigit.c\
              src/ft_isprint.c\
              src/ft_isspace.c\
              src/ft_itoa.c\
              src/ft_lstadd_back.c\
              src/ft_lstclear.c\
              src/ft_lstdelone.c\
              src/ft_lstiter.c\
              src/ft_lstlast.c\
              src/ft_lstmap.c\
              src/ft_lstsize.c\
              src/ft_memchr.c\
              src/ft_memcmp.c\
              src/ft_memcpy.c\
              src/ft_memmove.c\
              src/ft_memset.c\
              src/ft_putchar_fd.c\
              src/ft_putendl_fd.c\
              src/ft_putnbr_fd.c\
              src/ft_putstr_fd.c\
              src/ft_split.c\
              src/ft_strchr.c\
              src/ft_strdup.c\
              src/ft_striteri.c\
              src/ft_strjoin.c\
              src/ft_strlcat.c\
              src/ft_strlcpy.c\
              src/ft_strlen.c\
              src/ft_strmapi.c\
              src/ft_strncmp.c\
              src/ft_strnstr.c\
              src/ft_strrchr.c\
              src/ft_strtrim.c\
              src/ft_substr.c\
              src/ft_tolower.c\
              src/ft_toupper.c\
              src/get_next_line.c\
              src/get_next_line_utils.c\

OBJS		= ${patsubst src/%.c, obj/%.o, ${SRC}}
DEPS		= ${patsubst src/%.c, obj/%.d, ${SRC}}
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
AR			= ar -rcs
NAME		= bin/libft.a
DEPSFLAGS	= -MMD -MP
HBLU		= '\e[1;94m'
NC			= '\e[0m'

all : ${NAME}

${NAME} : ${OBJS}
	mkdir -p bin
	${AR} ${NAME} ${OBJS}

obj/%.o : src/%.c
	mkdir -p $(dir $@)
	printf ${HBLU}" [%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	${CC} ${CFLAGS} ${DEPSFLAGS} -Iinclude -I../include -c $< -o $@

clean :
	${RM} obj

fclean : clean
	${RM} bin

.PHONY : fclean clean all re
.SILENT : fclean clean $(OBJS) ${NAME}
-include : $(DEPS)
