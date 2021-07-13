/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:52:24 by dzuntini          #+#    #+#             */
/*   Updated: 2021/07/13 12:46:24 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_sens_fin2(t_pusw *lst, int pos)
{
	int	t_pos;

	t_pos = pos;
	if (pos > (lst->len_b / 2))
		t_pos = lst->len_b - pos;
	else
		t_pos++;
	return (t_pos);
}

int	find_sens_fin(t_pusw *lst)
{
	int	pos;
	int	pos2;

	pos = find_nb(lst->stack_b, lst->len_b, lst->max);
	pos2 = find_nb(lst->stack_b, lst->len_b, lst->max_n);
	if (find_sens_fin2(lst, pos) < find_sens_fin2(lst, pos2))
	{
		if (pos > (lst->len_b / 2))
			return (1);
		return (0);
	}
	if (pos2 > (lst->len_b / 2))
		return (1);
	return (0);
}

int	find_sens_pivot(t_pusw *lst)
{
	int	pos;
	int	pos2;

	pos2 = 0;
	pos = lst->len_a;
	while (pos2 <= lst->len_a && lst->stack_a[pos2] > lst->pivot)
		pos2++;
	while (pos >= 0 && lst->stack_a[pos] > lst->pivot)
		pos--;
	if ((lst->len_a - pos) == pos2 + 1)
	{
		if (lst->stack_a[pos] < lst->stack_a[pos2])
			return (1);
		return (0);
	}
	if ((lst->len_a - pos) < pos2 + 1)
		return (1);
	return (0);
}

void	find_pivot(t_pusw *lst)
{
	int	val;
	int	min;
	int	i;

	val = 11;
	i = -1;
	if (lst->len_a >= 40 && lst->len_a <= 300)
		val = (lst->len_a / 43) + 4;
	else if (lst->len_a < 40)
		val = 4;
	min = find_min(lst->stack_a, lst->len_a);
	while (++i < (lst->len_a / val))
		min = find_next_min(lst->stack_a, lst->len_a, min);
	lst->pivot = min;
}

int	find_sens(t_pusw *lst, int max)
{
	int	pos;

	pos = find_nb(lst->stack_b, lst->len_b, max);
	if (pos > (lst->len_b / 2))
		return (1);
	return (0);
}
