
SRC_F		= src/
PARCER		= src/parcer/
TOOLS		= src/parcer/tools/
SCENES		= src/parcer/scene/
OBJECTS		= src/parcer/objects/
LIBFT		= libft/

SRC			=	$(shell ls $(OBJECTS)*.c)\
				$(shell ls $(SCENES)*.c)\
				$(shell ls $(PARCER)*.c)\
				$(shell ls $(TOOLS)*.c)\
				$(shell ls $(SRC_F)minirt/*.c)\
				src/debug_tools.c
INCLUDES	= -Iinclude -Ilibft/include
OBJ_DIR 	= obj
FLAGS		= 
# -fsanitize=address -g
# -Wall -Wextra -Werror -fsanitize=address
NAME		= Minirt
LIBFT_NAME	= libft/bin/libft.a
CC			= cc
OBJ			= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
DEPS		= $(patsubst %.c, $(OBJ_DIR)/%.d, $(SRC))
DEPSFLAGS	= -MMD -MP
HBLU		= '\e[1;94m'
NC			= '\e[0m'

all : lib $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_NAME)  -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_DIR)/%.o : %.c Makefile
	mkdir -p $(dir $@)
	printf $(HBLU)"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(FLAGS) $(DEPSFLAGS) ${INCLUDES} -I/usr/include -Imlx_linux -c $< -o $@

lib:
	make -C ${LIBFT}

clean :
	make clean -C ${LIBFT}
	rm -rf $(OBJ_DIR)

fclean : clean
	make fclean -C ${LIBFT}
	rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean all

-include : $(DEPS)
.SILENT : $(NAME) clean fclean all ${OBJ} lib