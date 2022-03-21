#COMPILATION


CC			= clang++
CFLAGS		= -Wall -Wextra -Werror -pedantic -std=c++98
.DEFAULT_GOAL := all

#LIB

#LIBFT_M :
#	@make -C libft/ all
#
#LIBFT_C :
#	@make -C libft/ clean
#
#LIBFT_FC :
#	@make -C libft/ fclean
#
#LIBFT_N :
#	@make -C libft/ norme
#
#LIBFT_R :
#	@make -C libft/ re

#VALUES

NAME		= ex00
#LIBFT		= libft/libft.a

#MISC

NO_COLOR	= \033[1;36m	
OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

#SOURCES

SRC =		main.cpp 	\
			Fixed.cpp	\

$(NAME):
		$(CC) $(SRC) $(CFLAGS) -o $(NAME)

all:		$(NAME)

exe:		all
			./$(NAME)

clean:
			@rm -f *.o; rm -f *~
			@echo "${WARN_COLOR}temporary files removed"

fclean: clean
				@rm -f $(NAME)
				@echo "${KILL_COLOR}exec deleted"
				@echo "${NO_COLOR}"

re:		fclean all

.PHONY: all clean fclean re
