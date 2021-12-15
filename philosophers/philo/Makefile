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

NAME		= philo
LIBFT		= libft/libft.a

#MISC

NO_COLOR	= \033[1;36m	
OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

#SOURCES

CSRCS		=	ft_begin.c		\
				ft_utils.c		\
				main.c			\

COBJS		= ${CSRCS:.c=.o}

all:		$(NAME)

exe:		all
			./$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME):	${COBJS}
			@$(CC) $(CFLAGS) $(COBJS) -o $(NAME)
			@echo "${OK_COLOR}The others continents have monkeys"
			@echo "${KILL_COLOR}The Europe have frenchs,"
			@echo "${WARN_COLOR}This, compensate that"
clean:
			@rm -f *.o; rm -f *~
			@echo "${WARN_COLOR}temporary files removed"

fclean: clean
				@rm -f $(NAME)
				@echo "${KILL_COLOR}exec deleted"
				@echo "${NO_COLOR}"

re:		fclean all

.PHONY: all clean fclean re
