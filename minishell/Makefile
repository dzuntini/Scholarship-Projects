# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/25 13:56:27 by pcarella              #+#    #+#              #
#    Updated: 2021/10/11 17:13:50 by dzuntini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

NO_COLOR	= \033[1;36m
OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

CFLAGS	=	-Wall -Werror -Wextra -I ./include -I ~/.brew/opt/readline/include

SDIR	=	src

SRCS	=	src/builtin.c\
			src/builtin_cd.c\
			src/builtin_echo.c\
			src/builtin_env.c\
			src/builtin_exit.c\
			src/builtin_export1.c\
			src/builtin_export2.c\
			src/builtin_pwd.c\
			src/builtin_unset.c\
			src/error.c\
			src/exec.c\
			src/exec2.c\
			src/expanser.c\
			src/free.c\
			src/lexer.c\
			src/main.c\
			src/parser.c\
			src/parser2.c\
			src/redir.c\
			src/signal.c\
			src/syntax.c\
			src/tokenize.c\
			src/utils.c

OBJS =		$(SRCS:.c=.o)

all:		libft $(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) ./libft/libft.a -L ~/.brew/opt/readline/lib -lreadline -lncurses -o $(NAME)
			@echo "\n\n\n${WARN_COLOR}Minishell"
			@echo "${KILL_COLOR}Like a big shell but with small budget${NO_COLOR}"

libft:
			make -C ./libft

clean:
			make clean -C ./libft
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)
			make fclean -C ./libft

re: 		fclean all

.PHONY:		re clean fclean all libft
