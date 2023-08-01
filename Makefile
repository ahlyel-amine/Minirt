MNRT_SRC =	src/minirt/main.c \
			src/parcer/parcer.c src/parcer/tools.c src/parcer/color_parcer.c src/parcer/cordinate_parcer.c\
			src/parcer/objects/cylender_parcer.c src/parcer/objects/plane_parcer.c src/parcer/objects/sphere_parcer.c\
			src/parcer/scene/camera_parcer.c src/parcer/scene/light_parcer.c src/parcer/scene/lighting_parcer.c\
			

LIBFT	=	libft/ft_atoi.c	libft/ft_calloc.c libft/ft_isspace.c libft/ft_putendl_fd.c libft/ft_strdup.c libft/ft_strncmp.c libft/get_next_line_utils.c \
			libft/ft_bzero.c libft/ft_isdigit.c libft/ft_memset.c libft/ft_substr.c libft/ft_split.c  libft/ft_memcpy.c libft/ft_strlen.c libft/get_next_line.c\
			libft/newobject.c libft/addobject_front.c libft/ft_atod.c\

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