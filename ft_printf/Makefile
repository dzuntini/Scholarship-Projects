#COMPILATION

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INC			= -I.

#VALUES
NAME		= libftprintf.a

#MISC

NO_COLOR	= \033[1;36m	
OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

#SOURCES

FILES		= 	ft_printf.c		\
				ft_analyse.c	\
				ft_convert.c	\
				ft_utils.c		\
				ft_infos.c		\
				ft_ternary.c

OBJS		= ${FILES:.c=.o}

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME):	${OBJS}
			ar -cr $(NAME) $(OBJS) ft_printf.h 
			@echo "${OK_COLOR}lib created and ready"



all:	${NAME}

clean:
			@rm -f *.o; rm -f *~
			@echo "${WARN_COLOR}temporary files removed"

fclean: clean
				@rm -f $(NAME)
				@echo "${KILL_COLOR}lib deleted"
				@echo "${NO_COLOR}"

bonus: 	${OBJS} ${BON}
			ar -cr $(NAME) $(OBJS) ${BON} libft.h 
			@echo "${OK_COLOR}lib + bonus created and ready"

re:		fclean all

.PHONY: all clean fclean re
