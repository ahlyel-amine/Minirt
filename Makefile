SRC_F				= src
MINIRT_F			= $(SRC_F)/minirt
PARCER_F			= $(SRC_F)/parcer
TOOLS_F				= $(PARCER_F)/tools
SCENES_F			= $(PARCER_F)/scene
OBJECTS_F			= $(PARCER_F)/objects
TRACER_F			= $(SRC_F)/tracer
INTERSECTION_F		= $(TRACER_F)/intersections
VEC_OP_F			= $(TRACER_F)/vec_operations
LIBFT				= libft/

BNS_SRC_F			= bonus/src_bonus
BNS_MINIRT_F		= $(BNS_SRC_F)/minirt_bonus
BNS_PARCER_F		= $(BNS_SRC_F)/parcer_bonus
BNS_TOOLS_F			= $(BNS_PARCER_F)/tools_bonus
BNS_SCENES_F		= $(BNS_PARCER_F)/scene_bonus
BNS_OBJECTS_F		= $(BNS_PARCER_F)/objects_bonus
BNS_TRACER_F		= $(BNS_SRC_F)/tracer_bonus
BNS_INTERSECTION_F	= $(BNS_TRACER_F)/intersections_bonus
BNS_VEC_OP_F		= $(BNS_TRACER_F)/vec_operations_bonus

SRC				= $(MINIRT_F)/main.c \
				  $(TOOLS_F)/addobject_front.c \
                  $(TOOLS_F)/ft_atod.c \
                  $(TOOLS_F)/tools.c \
                  $(TOOLS_F)/newobject.c \
                  $(SCENES_F)/camera_parcer.c \
                  $(SCENES_F)/lighting_parcer.c \
                  $(SCENES_F)/light_parcer.c \
                  $(PARCER_F)/color_parcer.c \
                  $(PARCER_F)/cordinate_parcer.c \
                  $(PARCER_F)/parcer.c \
                  $(OBJECTS_F)/cylender_parcer.c \
                  $(OBJECTS_F)/plane_parcer.c \
                  $(OBJECTS_F)/sphere_parcer.c \
                  $(TRACER_F)/camera.c \
                  $(TRACER_F)/hooks_obj_move.c \
                  $(TRACER_F)/hooks_obj_scale.c \
                  $(TRACER_F)/light.c \
                  $(TRACER_F)/pixels.c \
                  $(TRACER_F)/raytracing.c \
                  $(TRACER_F)/rt_hooks.c \
                  $(TRACER_F)/tracer.c \
                  $(VEC_OP_F)/operations_on_vec.c \
                  $(VEC_OP_F)/vec_operations.c \
                  $(VEC_OP_F)/vec_tools2.c \
                  $(VEC_OP_F)/vec_tools.c \
                  $(INTERSECTION_F)/cylender_intersections.c \
                  $(INTERSECTION_F)/intersection.c \
                  $(INTERSECTION_F)/plane_intersections.c \
                  $(INTERSECTION_F)/sphere_intersections.c \
                  src/debug_tools.c \

BNS_SRC			= $(BNS_MINIRT_F)/main_bonus.c \
                  $(BNS_MINIRT_F)/multithreading_managment_bonus.c \
                  $(BNS_TOOLS_F)/addobject_front_bonus.c \
                  $(BNS_TOOLS_F)/ft_atod_bonus.c \
                  $(BNS_TOOLS_F)/newobject_bonus.c \
                  $(BNS_TOOLS_F)/tools_bonus2.c \
                  $(BNS_TOOLS_F)/tools_bonus.c \
                  $(BNS_SCENES_F)/camera_parcer_bonus.c \
                  $(BNS_SCENES_F)/lighting_parcer_bonus.c \
                  $(BNS_SCENES_F)/light_parcer_bonus.c \
                  $(BNS_PARCER_F)/color_parcer_bonus.c \
                  $(BNS_PARCER_F)/cordinate_parcer_bonus.c \
                  $(BNS_PARCER_F)/features_checker_bonus.c \
                  $(BNS_PARCER_F)/parcer_bonus.c \
                  $(BNS_PARCER_F)/parcer_features_bonus.c \
                  $(BNS_OBJECTS_F)/cone_parcer_bonus.c \
                  $(BNS_OBJECTS_F)/cylender_parcer_bonus.c \
                  $(BNS_OBJECTS_F)/plane_parcer_bonus.c \
                  $(BNS_OBJECTS_F)/sphere_parcer_bonus.c \
                  $(BNS_OBJECTS_F)/triangle_parcer_bonus.c \
                  $(BNS_TRACER_F)/bump_container.c \
                  $(BNS_TRACER_F)/camera_bonus.c \
                  $(BNS_TRACER_F)/checkerboard_pattern_bonus.c \
                  $(BNS_TRACER_F)/hooks_cam_move.c \
                  $(BNS_TRACER_F)/hooks_obj_move_bonus.c \
                  $(BNS_TRACER_F)/hooks_obj_scale_bonus.c \
                  $(BNS_TRACER_F)/light_bonus.c \
                  $(BNS_TRACER_F)/pixels_bonus.c \
                  $(BNS_TRACER_F)/raytracing_bonus.c \
                  $(BNS_TRACER_F)/rt_hooks_bonus.c \
                  $(BNS_TRACER_F)/texture_binding_bonus.c \
                  $(BNS_TRACER_F)/texture_process_bonus.c \
                  $(BNS_TRACER_F)/tools_bonus.c \
                  $(BNS_TRACER_F)/tracer_bonus.c \
                  $(BNS_VEC_OP_F)/operations_on_vec_bonus.c \
                  $(BNS_VEC_OP_F)/vec_operations_bonus.c \
                  $(BNS_VEC_OP_F)/vec_tools2_bonus.c \
                  $(BNS_VEC_OP_F)/vec_tools_bonus.c \
                  $(BNS_INTERSECTION_F)/cone_intersections_bonus.c \
                  $(BNS_INTERSECTION_F)/cylender_intersections_bonus.c \
                  $(BNS_INTERSECTION_F)/intersection_bonus.c \
                  $(BNS_INTERSECTION_F)/plane_intersections_bonus.c \
                  $(BNS_INTERSECTION_F)/sphere_intersections_bonus.c \
                  $(BNS_INTERSECTION_F)/triangle_intersections_bonus.c \
                  bonus/src_bonus/debug_tools_bonus.c

INCLUDES		= -Iinclude -Ilibft/include
BNS_INCLUDES	= -Ibonus/include_bonus -Ilibft/include
OBJ_DIR 		= obj
BNS_OBJ_DIR 	= obj_bonus
CFLAGS			= -Wall -Wextra -Werror
GFLAGS			= -lmlx -Ofast -framework OpenGL -framework AppKit
NAME			= Minirt
BNS_NAME		= Minirt_bonus
LIBFT_NAME		= libft/bin/libft.a
CC				= cc
OBJ				= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
BNS_OBJ			= $(patsubst %.c, $(BNS_OBJ_DIR)/%.o, $(BNS_SRC))
DEPS			= $(patsubst %.c, $(OBJ_DIR)/%.d, $(SRC))
BNS_DEPS		= $(patsubst %.c, $(BNS_OBJ_DIR)/%.d, $(BNS_SRC))
DEPSFLAGS		= -MMD -MP
HBLU			= '\e[1;94m'
NC				= '\e[0m'
THEME 			= \
'                                                                                                                                                                                                  '\
'                                bbbbbbbb                                                                                                                                                          '\
'               AAA              b::::::b                                              lllllll                          tttt                            RRRRRRRRRRRRRRRRR   TTTTTTTTTTTTTTTTTTTTTTT'\
'              A:::A             b::::::b                                              l:::::l                       ttt:::t                            R::::::::::::::::R  T:::::::::::::::::::::T'\
'             A:::::A            b::::::b                                              l:::::l                       t:::::t                            R::::::RRRRRR:::::R T:::::::::::::::::::::T'\
'            A:::::::A            b:::::b                                              l:::::l                       t:::::t                            RR:::::R     R:::::RT:::::TT:::::::TT:::::T'\
'           A:::::::::A           b:::::bbbbbbbbb        ssssssssss      ooooooooooo    l::::l uuuuuu    uuuuuuttttttt:::::ttttttt        eeeeeeeeeeee    R::::R     R:::::RTTTTTT  T:::::T  TTTTTT'\
'          A:::::A:::::A          b::::::::::::::bb    ss::::::::::s   oo:::::::::::oo  l::::l u::::u    u::::ut:::::::::::::::::t      ee::::::::::::ee  R::::R     R:::::R        T:::::T        '\
'         A:::::A A:::::A         b::::::::::::::::b ss:::::::::::::s o:::::::::::::::o l::::l u::::u    u::::ut:::::::::::::::::t     e::::::eeeee:::::eeR::::RRRRRR:::::R         T:::::T        '\
'        A:::::A   A:::::A        b:::::bbbbb:::::::bs::::::ssss:::::so:::::ooooo:::::o l::::l u::::u    u::::utttttt:::::::tttttt    e::::::e     e:::::eR:::::::::::::RR          T:::::T        '\
'       A:::::A     A:::::A       b:::::b    b::::::b s:::::s  ssssss o::::o     o::::o l::::l u::::u    u::::u      t:::::t          e:::::::eeeee::::::eR::::RRRRRR:::::R         T:::::T        '\
'      A:::::AAAAAAAAA:::::A      b:::::b     b:::::b   s::::::s      o::::o     o::::o l::::l u::::u    u::::u      t:::::t          e:::::::::::::::::e R::::R     R:::::R        T:::::T        '\
'     A:::::::::::::::::::::A     b:::::b     b:::::b      s::::::s   o::::o     o::::o l::::l u::::u    u::::u      t:::::t          e::::::eeeeeeeeeee  R::::R     R:::::R        T:::::T        '\
'    A:::::AAAAAAAAAAAAA:::::A    b:::::b     b:::::bssssss   s:::::s o::::o     o::::o l::::l u:::::uuuu:::::u      t:::::t    tttttte:::::::e           R::::R     R:::::R        T:::::T        '\
'   A:::::A             A:::::A   b:::::bbbbbb::::::bs:::::ssss::::::so:::::ooooo:::::ol::::::lu:::::::::::::::uu    t::::::tttt:::::te::::::::e        RR:::::R     R:::::R      TT:::::::TT      '\
'  A:::::A               A:::::A  b::::::::::::::::b s::::::::::::::s o:::::::::::::::ol::::::l u:::::::::::::::u    tt::::::::::::::t e::::::::eeeeeeeeR::::::R     R:::::R      T:::::::::T      '\
' A:::::A                 A:::::A b:::::::::::::::b   s:::::::::::ss   oo:::::::::::oo l::::::l  uu::::::::uu:::u      tt:::::::::::tt  ee:::::::::::::eR::::::R     R:::::R      T:::::::::T      '\
'AAAAAAA                   AAAAAAAbbbbbbbbbbbbbbbb     sssssssssss       ooooooooooo   llllllll    uuuuuuuu  uuuu        ttttttttttt      eeeeeeeeeeeeeeRRRRRRRR     RRRRRRR      TTTTTTTTTTT      '\
'                                                                                                                                                                                                  '

all : lib $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) ${GFLAGS} -o $(NAME)

$(OBJ_DIR)/%.o : %.c include/ Makefile
	@echo $(THEME)
	mkdir -p $(dir $@)
	printf $(HBLU)"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) $(DEPSFLAGS) ${INCLUDES} -Ofast -Imlx -c $< -o $@

$(BNS_OBJ_DIR)/%.o : %.c bonus/include_bonus/ Makefile
	mkdir -p $(dir $@)
	printf $(HBLU)"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) $(DEPSFLAGS) ${BNS_INCLUDES} -Ofast -Imlx -c $< -o $@

bonus : lib $(BNS_OBJ)
	$(CC) $(CFLAGS) $(BNS_OBJ) $(LIBFT_NAME) ${GFLAGS} -o $(BNS_NAME)	

lib:
	make -C ${LIBFT}

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