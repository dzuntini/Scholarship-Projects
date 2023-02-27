/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:53:24 by dzuntini          #+#    #+#             */
/*   Updated: 2021/08/22 21:56:30 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	long long	nb;
	int			cpt;
	int			sign;

	cpt = 0;
	sign = 1;
	nb = 0;
	while (str[cpt] == ' ' || (9 <= str[cpt] && str[cpt] <= 13))
		cpt++;
	if (str[cpt] == '-' || str[cpt] == '+')
	{
		if (str[cpt] == '-')
			sign *= -1;
		cpt++;
	}
	while ('0' <= str[cpt] && str[cpt] <= '9')
		nb = nb * 10 + str[cpt++] - '0';
	return ((long long)sign * nb);
}
