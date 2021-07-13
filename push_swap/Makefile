#COMPILATION


CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
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

NAME		= push_swap
LIBFT		= libft/libft.a

#MISC

NO_COLOR	= \033[1;36m	
OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

#SOURCES

CSRCS		=	ft_algo1.c		\
				ft_algo.c		\
				ft_check.c		\
				ft_nbrfind.c	\
				ft_posfind.c	\
				ft_push.c		\
				ft_rrotate.c	\
				ft_rotate.c		\
				ft_swap.c		\
				ft_utils.c		\
				main.c			\

COBJS		= ${CSRCS:.c=.o}

all:		LIBFT_M $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME):	${COBJS}
			@$(CC) $(CFLAGS) $(COBJS) $(LIBFT) -o $(NAME) 
			@echo "${OK_COLOR}exec made"
			@echo "${KILL_COLOR}"

clean:
			@rm -f *.o; rm -f *~
			@echo "${WARN_COLOR}temporary files removed"

fclean: clean
				@rm -f $(NAME)
				@echo "${KILL_COLOR}exec deleted"
				@echo "${NO_COLOR}"

re:		fclean LIBFT_R all

.PHONY: all clean fclean re
