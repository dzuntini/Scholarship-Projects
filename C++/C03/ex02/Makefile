#COMPILATION
CC			= clang++
CFLAGS		= -Wall -Wextra -Werror -pedantic -std=c++98
.DEFAULT_GOAL := re

#VALUES
NAME		= ex02
#MISC

NO_COLOR	= \033[1;36m	
OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

#SOURCES

SRC =		main.cpp 	\
			Claptrap.cpp \
			ScavTrap.cpp	\
			FragTrap.cpp
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
