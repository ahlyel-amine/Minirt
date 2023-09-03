SRC			= $(shell ls src/*.c)
OBJS		= ${patsubst src/%.c, obj/%.o, ${SRC}}
DEPS		= ${patsubst src/%.c, obj/%.d, ${SRC}}
CC			= cc
CFLAGS		= 
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

obj/%.o : src/%.c Makefile
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
