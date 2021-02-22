#COMPILATION

CC			= gcc
CFLAGS		= -v -Wall -Wextra -Werror
INC			= -I.

#DIRECTORIES

SDIR		= 	./srcs
ODIR		= 	./obj/

#VALUES
NAME		= libft.a

#MISC

OK_COLOR	= \033[0;32m
KILL_COLOR	= \033[0;31m
WARN_COLOR	= \033[0;33m

#MACRO

OBJ			:= $(SDIR:%.c=$(ODIR)/%.o)

#SOURCES

SRC 		:=	$(addprefix $(SDIR)/, $(FLIES))
FLIES		:=	ft_atoi.c	\
				ft_fibonacci.c	\
				ft_find_next_prime.c	\
				ft_is_prime.c	\
				ft_putchar.c	\
				ft_putnbr.c	\
				ft_putstr.c	\
				ft_rev_int_tab.c	\
				ft_sort_int_tab.c	\
				ft_sqrt.c	\
				ft_str_is_alpha.c	\
				ft_str_is_lowercase.c	\
				ft_str_is_numeric.c	\
				ft_str_is_printable.c	\
				ft_str_is_uppercase.c	\
				ft_strcapitalize.c	\
				ft_strcat.c	\
				ft_strcmp.c	\
				ft_strcpy.c	\
				ft_strdup.c	\
				ft_strjoin.c	\
				ft_strlcat.c	\
				ft_strlcpy.c	\
				ft_strlen.c	\
				ft_strlowcase.c	\
				ft_strncat.c	\
				ft_strncmp.c	\
				ft_strncpy.c	\
				ft_strstr.c	\
				ft_strupcase.c	\
				ft_swap.c	\
				ft_ultimate_div_mod.c	\
				ft_ultimate_ft.c	\
				ft_ultimate_range.c
				#rft_calloc.c
				#rft_split.c

${NAME}:	${OBJ}
			@ar -crs $(NAME) $(ODIR)*.o
			@echo "${OK_COLOR}lib created and ready"

$(ODIR)/%.o: $(SDIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

all:	${NAME}

clean:
			@rm -f *.o; rm -f *~
			@echo "${WARN_COLOR}temporary files removed"

fclean: clean
				@rm -f $(NAME)
				@rm -f $(ODIR)*.o
				@echo "${KILL_COLOR}lib deleted"

re:		fclean all

.PHONY: all clean fclean re