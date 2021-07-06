/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 23:01:50 by dzuntini          #+#    #+#             */
/*   Updated: 2021/06/29 12:00:42 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "client.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		ft_putchar(str[i++]);
}

void	ft_putnbr(int nb)
{
	unsigned int	n;

	if (nb < 0)
	{
		n = -nb;
		ft_putchar('-');
	}
	else
		n = nb;
	if (n > 9)
	{
		ft_putnbr(n / 10);
		n = n % 10;
	}
	ft_putchar(n + '0');
}
