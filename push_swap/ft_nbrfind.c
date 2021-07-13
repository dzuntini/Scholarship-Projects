/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:14:10 by dzuntini          #+#    #+#             */
/*   Updated: 2021/07/08 12:44:45 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min(int *stack, int len)
{
	int	min;

	min = 2147483647;
	while (len >= 0)
	{
		if (stack[len] < min)
			min = stack[len];
		len--;
	}
	return (min);
}

int	find_max(int *stack, int len)
{
	int	max;

	max = -2147483648;
	while (len >= 0)
	{
		if (stack[len] > max)
			max = stack[len];
		len--;
	}
	return (max);
}

int	find_next_min(int *stack, int len, int tmp)
{
	int	min;

	min = 2147483647;
	while (len >= 0)
	{
		if (stack[len] < min && stack[len] > tmp)
			min = stack[len];
		len--;
	}
	return (min);
}

int	find_next_max(int *stack, int len, int tmp)
{
	int	max;

	max = -2147483648;
	while (len >= 0)
	{
		if (stack[len] > max && stack[len] < tmp)
			max = stack[len];
		len--;
	}
	return (max);
}

int	find_nb(int *stack, int len, int nb)
{
	while (len >= 0)
	{
		if (stack[len] == nb)
			return (len);
		len--;
	}
	return (0);
}
