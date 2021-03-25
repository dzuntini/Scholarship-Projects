/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   ft_ternary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:33:06 by dzuntini          #+#    #+#             */
/*   Updated: 2021/03/23 14:23:13 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ternary(int a, int tr, int fl)
{
	if (a)
		return (tr);
	else
		return (fl);
}

void	ft_padding(int cond, int prec, char c)
{
	if (cond)
		padding(prec, c);
}

void	ft_dpadding(t_option *o, int nb)
{
	if (o->flag_minus == 0 && o->width > o->a_p)
	{
		if (o->flag_zero == 1 && o->dot < 0)
		{
			if (nb < 0)
				ft_putchar('-', 1);
			padding(o->width - o->a_p, '0');
		}
		else
			padding(o->width - o->a_p, ' ');
	}
	if (nb < 0)
		if (!(o->width > o->a_p && o->flag_zero == 1 \
			  && o->dot < 0 && o->flag_minus == 0))
			ft_putchar('-', 1);
}
