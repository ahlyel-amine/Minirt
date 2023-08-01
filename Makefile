MNRT_SRC =	src/minirt/main.c
			

LIBFT	=	libft/ft_atoi.c	libft/ft_calloc.c libft/ft_isspace.c libft/ft_putendl_fd.c libft/ft_strdup.c libft/ft_strncmp.c libft/get_next_line_utils.c \
			libft/ft_bzero.c libft/ft_isdigit.c libft/ft_memset.c libft/ft_substr.c libft/ft_split.c  libft/ft_memcpy.c libft/ft_strlen.c libft/get_next_line.c\
			libft/ft_lstnew.c libft/ft_lstadd_front.c\

SRC		=	${MNRT_SRC} ${LIBFT}
OBJ_DIR = obj
HEADERS = include/*.h
FLAGS = -Wall -Wextra -Werror -fsanitize=address
NAME = minirt
CC = cc
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all : $(NAME)
	
$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c $(HEADERS) 
	mkdir -p $(dir $@)
	printf $(HBLU)"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : $(NAME) clean fclean all
.SILENT : $(NAME) clean fclean all ${OBJ}