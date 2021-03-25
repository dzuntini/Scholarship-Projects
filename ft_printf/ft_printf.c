/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:30:09 by dzuntini          #+#    #+#             */
/*   Updated: 2021/03/22 11:32:16 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Count number of character to avoid pulling it up everywhere
*/
int	g_count;

int	ft_putchar(char c, int on)
{
	if (on != 0)
	{
		write(1, &c, 1);
		g_count++;
	}
	return (1);
}

int	ft_printf(const char *format, ...)
{
	char		*toformat;
	t_option	o;
	va_list		args;

	g_count = 0;
	toformat = (char *)format;
	va_start(args, format);
	while (*toformat)
	{
		if (*toformat == '%')
		{
			toformat++;
			o = *analyze_format(toformat, args, ft_init_option(&o));
			convert_type_format(&o, args);
			toformat = toformat + len_filter(toformat) + 1;
		}
		else
			ft_putchar(*toformat++, 1);
	}
	va_end(args);
	return (g_count);
}
