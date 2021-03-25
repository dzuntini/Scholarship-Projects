/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:31:28 by dzuntini          #+#    #+#             */
/*   Updated: 2021/03/23 14:47:45 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_option
{
	int		flag_minus;
	int		flag_zero;
	int		width;
	int		dot;
	int		a_p;
	char	type;
}				t_option;

int				ft_printf(const char *format, ...);
int				ft_putchar(char c, int on);
int				ft_putstr(char *str, int prec, int on);
int				ft_strlen(const char *s);
int				ft_intlen(long int n);
void			padding(int i, char c);
int				ft_atoi(const char *str);
int				ft_putnbr_base(long long nbr, char *base, int on);
int				ft_putptr_base(unsigned long int nbr, char *base, int on);
int				find_converter(char str, char *charset);
char			*set_base(char c);
void			analyze_flags(char *s, va_list args, t_option *o);
void			convert_s(char *s, t_option *o, int i);
void			convert_di(int nb, t_option *o, int i);
void			convert_uxx(unsigned int nb, t_option *o, int i);
void			convert_p(unsigned long int nb, t_option *o, int i);
void			convert_c_other(va_list args, t_option *o);
void			convert_type_format(t_option *o, va_list args);
size_t			len_filter(char *toformat);
t_option		*analyze_format(char *toformat, va_list args, t_option *o);
t_option		*ft_init_option(t_option *o);

int				ft_ternary(int a, int tr, int fl);
void			ft_padding(int cond, int prec, char c);
void			ft_dpadding(t_option *o, int nb);
#endif
