/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:47:07 by dzuntini          #+#    #+#             */
/*   Updated: 2021/07/08 19:17:10 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "push_swap.h"

static int	ft_lettercheck(int ac, char **av)
{
	ac--;
	while (ac >= 1)
	{
		if (ft_strnbr(av[ac]) == 0)
			return (0);
		ac--;
	}
	return (1);
}

static int	ft_limitcheck(int ac, char **av)
{
	long	t;

	ac--;
	while (ac >= 1)
	{
		t = ft_atoi(av[ac]);
		if (t > 0 && t > INT_MAX)
			return (0);
		if (t < 0 && t < INT_MIN)
			return (0);
		ac--;
	}
	return (1);
}

static int	ft_doubloncheck(int ac, char **av, int m)
{
	int	i;

	while (ac > 1)
	{
		ac--;
		i = ac - 1;
		while (i >= m)
		{
			if (ft_atoi(av[i]) == ft_atoi(av[ac]))
				return (0);
			i--;
		}
	}
	return (1);
}

int	ft_ordercheck(int *list, int lim)
{
	int	i;

	i = 0;
	while (i < lim)
	{
		if (list[i] > list[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	ft_check(int ac, char **av, int m)
{
	m = !m;
	if (ft_lettercheck(ac, av))
		if (ft_limitcheck(ac, av))
			if (ft_doubloncheck(ac, av, m))
				return (1);
	ft_error();
	return (0);
}
