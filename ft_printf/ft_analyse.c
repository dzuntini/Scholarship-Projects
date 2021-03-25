/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:32:10 by dzuntini          #+#    #+#             */
/*   Updated: 2021/03/22 11:21:16 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_option	*ft_init_option(t_option *o)
{
	o->flag_minus = 0;
	o->flag_zero = 0;
	o->width = 0;
	o->dot = -1;
	o->a_p = 0;
	o->type = 0;
	return (o);
}

int	find_converter(char str, char *charset)
{
	ssize_t	k;

	k = -1;
	while (charset[++k])
		if (str == charset[k])
			return (charset[k]);
	return (0);
}

void	analyze_flags(char *s, va_list args, t_option *o)
{
	if (*s == '-')
		o->flag_minus = 1;
	else if (*s == '.')
		o->dot = 0;
	else if (*s == '0' && (*(s - 1) < '0' || *(s - 1) > '9'))
		o->flag_zero = 1;
	else if (*s == '*')
	{
		if (*(s - 1) != '.')
		{
			if (o->width < 0)
				o->flag_minus = 1;
			o->width = va_arg(args, int);
		}
		if (*(s - 1) == '.')
			o->dot = va_arg(args, int);
	}
}

t_option	*analyze_format(char *toformat, va_list args, t_option *o)
{
	ssize_t	i;

	i = -1;
	while (find_converter(toformat[++i], "0123456789.-*") && toformat[i])
	{
		if ((find_converter(toformat[i], "0-.*")) != 0)
			analyze_flags(&toformat[i], args, o);
		if (find_converter(toformat[i], "123456789"))
		{
			if (toformat[i - 1] == '.')
				i = i + ft_intlen(o->dot = ft_atoi(&toformat[i])) - 1;
			else if (toformat[i - 1] != '.')
				i = i + ft_intlen(o->width = ft_atoi(&toformat[i])) - 1;
		}
	}
	o->type = toformat[i];
	return (o);
}

void	convert_type_format(t_option *o, va_list args)
{
	int	i;

	i = 0;
	if (o->width < 0)
	{
		o->flag_minus = 1;
		o->width = -o->width;
	}
	if (o->type == 's')
		convert_s(va_arg(args, char *), o, i);
	else if (o->type == 'p')
		convert_p(va_arg(args, long long), o, i);
	else if (o->type == 'd' || o->type == 'i')
		convert_di(va_arg(args, int), o, i);
	else if (o->type == 'X' || o->type == 'x' || o->type == 'u')
		convert_uxx(va_arg(args, unsigned int), o, i);
	else
		convert_c_other(args, o);
}
