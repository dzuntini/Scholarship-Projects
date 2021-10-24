#COMPILATION


CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit
INC			= -I.
.DEFAULT_GOAL := all

#LIB

LIBFT_M : 
	@make -C libft/ all

LIBFT_C : 
	@make -C libft/ clean

LIBFT_FC : 
	@make -C libft/ fclean

LIBFT_N : 
	@make -C libft/ norme

LIBFT_R : 
	@make -C libft/ re

#VALUES

NAME		= so_long
LIBFT		= libft/libft.a

#MISC

NO_COLOR	= \033[1;36m	
OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

#SOURCES

CSRCS		=	ft_checker.c	\
				ft_hook.c		\
				ft_collision.c	\
				ft_readmap.c	\
				ft_free.c		\
				ft_getter.c		\
				ft_setter.c		\
				main.c			\

COBJS		= ${CSRCS:.c=.o}

all:		LIBFT_M $(NAME)

exe:		all
			./$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME):	${COBJS}
			@$(CC) $(CFLAGS) $(MLX_FLAGS) $(COBJS) $(LIBFT) -o $(NAME)
			@echo "${OK_COLOR}So long"
			@echo "${KILL_COLOR}And thanks for the fish"

clean:
			@rm -f *.o; rm -f *~
			@echo "${WARN_COLOR}temporary files removed"

fclean: clean
				@rm -f $(NAME)
				@echo "${KILL_COLOR}exec deleted"
				@echo "${NO_COLOR}"

re:		fclean LIBFT_R all

.PHONY: all clean fclean re
