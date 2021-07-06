#COMPILATION


CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INC			= -I.

#VALUES
NAME		= client
SNAME		= server

#MISC

NO_COLOR	= \033[1;36m	
OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

#SOURCES

CSRCS		= 	client.c	\
				ft_verif.c	\
				ft_putnbr.c

SSRCS		=	server.c	\
				ft_putnbr.c

COBJS		= ${CSRCS:.c=.o}

SOBJS		= ${SSRCS:.c=.o}

all:		$(NAME) $(SNAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(SNAME):	${SOBJS}
			@$(CC) $(CFLAGS) $(SOBJS) -o $(SNAME) 
			@echo "${OK_COLOR}server made"

$(NAME):	${COBJS}
			@$(CC) $(CFLAGS) $(COBJS) -o $(NAME) 
			@echo "${OK_COLOR}client made"
			@echo "${KILL_COLOR}"

clean:
			@rm -f *.o; rm -f *~
			@echo "${WARN_COLOR}temporary files removed"

fclean: clean
				@rm -f $(NAME) $(SNAME)
				@echo "${KILL_COLOR}execs deleted"
				@echo "${NO_COLOR}"

re:		fclean all

.PHONY: all clean fclean re
