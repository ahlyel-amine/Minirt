

SRC_F		= src/
PARCER		= src/parcer/
TOOLS		= src/parcer/tools/
SCENES		= src/parcer/scene/
OBJECTS		= src/parcer/objects/
LIBFT		= libft/
BNS_LIBFT		= libft/

BNS_SRC_F		= bonus/src_bonus/
BNS_PARCER		= bonus/src_bonus/parcer_bonus/
BNS_TOOLS		= bonus/src_bonus/parcer_bonus/tools_bonus/
BNS_SCENES		= bonus/src_bonus/parcer_bonus/scene_bonus/
BNS_OBJECTS		= bonus/src_bonus/parcer_bonus/objects_bonus/


SRC			=	$(shell ls $(OBJECTS)*.c)\
				$(shell ls $(SCENES)*.c)\
				$(shell ls $(PARCER)*.c)\
				$(shell ls $(TOOLS)*.c)\
				$(shell ls $(SRC_F)/*.c)\
				$(shell ls 'src/tracer/'*.c)\
				$(shell ls 'src/tracer/intersections/'*.c)\
				$(shell ls 'src/tracer/vec_operations/'*.c)\
				src/minirt/main.c
				

BNS_SRC			=	$(shell ls $(BNS_OBJECTS)*.c)\
				$(shell ls $(BNS_SCENES)*.c)\
				$(shell ls $(BNS_PARCER)*.c)\
				$(shell ls $(BNS_TOOLS)*.c)\
				$(shell ls $(BNS_SRC_F)minirt_bonus/*.c)\
				$(shell ls 'bonus/src_bonus/tracer_bonus/'*.c)\
				$(shell ls 'bonus/src_bonus/tracer_bonus/intersections_bonus/'*.c)\
				$(shell ls 'bonus/src_bonus/tracer_bonus/vec_operations_bonus/'*.c)\
				bonus/src_bonus/debug_tools_bonus.c

INCLUDES	= -Iinclude -Ilibft/include
BNS_INCLUDES	= -Ibonus/include_bonus -Ilibft/include
OBJ_DIR 	= obj
BNS_OBJ_DIR 	= obj_bonus
FLAGS		= 
#-fsanitize=address -g
# -Wall -Wextra -Werror -fsanitize=address
NAME		= Minirt
BNS_NAME		= Minirt_bonus
LIBFT_NAME	= libft/bin/libft.a
CC			= cc
OBJ			= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
BNS_OBJ			= $(patsubst %.c, $(BNS_OBJ_DIR)/%.o, $(BNS_SRC))
DEPS		= $(patsubst %.c, $(OBJ_DIR)/%.d, $(SRC))
BNS_DEPS		= $(patsubst %.c, $(BNS_OBJ_DIR)/%.d, $(BNS_SRC))
DEPSFLAGS	= -MMD -MP
HBLU		= '\e[1;94m'
NC			= '\e[0m'


all : lib $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT_NAME)  -lmlx -Ofast -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ_DIR)/%.o : %.c include/
	mkdir -p $(dir $@)
	printf $(HBLU)"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(FLAGS) $(DEPSFLAGS) ${INCLUDES} -Ofast -Imlx -c $< -o $@

lib:
	make -C ${LIBFT}

$(BNS_OBJ_DIR)/%.o : %.c bonus/include_bonus/
	mkdir -p $(dir $@)
	printf $(HBLU)"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(FLAGS) $(DEPSFLAGS) -Ibonus/include_bonus -Ilibft/include -Ofast -Imlx -c $< -o $@

bonus : lib $(BNS_OBJ)
	$(CC) $(FLAGS) $(BNS_OBJ) $(LIBFT_NAME)   -lmlx -Ofast -framework OpenGL -framework AppKit -o $(BNS_NAME)
	


clean :
	make clean -C ${LIBFT}
	rm -rf $(OBJ_DIR) $(BNS_OBJ_DIR)

fclean : clean
	make fclean -C ${LIBFT}
	rm -rf $(NAME) $(BNS_NAME)

re : fclean all

.PHONY : clean fclean all  bonus

-include : $(DEPS)  $(BNS_DEPS)
.SILENT : $(NAME) clean fclean all ${OBJ} lib bonus $(BNS_OBJ)