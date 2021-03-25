/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:33:29 by dzuntini          #+#    #+#             */
/*   Updated: 2021/03/22 11:31:48 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				posneg;
	int				result;

	i = 0;
	result = 0;
	posneg = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			posneg = -1;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (result * posneg);
}

int	ft_putptr_base(unsigned long int nb, char *base, int on)
{
	static int		i;
	unsigned int	baselen;

	baselen = ft_strlen(base);
	i = 0;
	if (nb == baselen)
		i += ft_putchar(base[1], on);
	if (nb > baselen)
		ft_putptr_base((nb / baselen), base, on);
	i += ft_putchar(base[nb % baselen], on);
	return (i);
}

int	ft_putnbr_base(long long nb, char *base, int on)
{
	static int	i;
	int			baselen;

	baselen = ft_strlen(base);
	i = 0;
	if (nb < 0)
	{
		ft_putchar('-', 0);
		nb = -nb;
	}
	if (nb == baselen)
		i += ft_putchar(base[1], on);
	if (nb > baselen)
		ft_putnbr_base((nb / baselen), base, on);
	i += ft_putchar(base[nb % baselen], on);
	return (i);
}

int	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

int	ft_intlen(long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
