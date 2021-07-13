/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_algo.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: dzuntini <dzuntini@student.42nice.fr>		+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/07/06 21:03:59 by dzuntini		   #+#	  #+#			  */
/*   Updated: 2021/07/13 12:41:38 by dzuntini         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_final(t_pusw *lst, char sens)
{
	while (lst->len_b != -1)
	{
		if (lst->len_b == 0 || lst->stack_b[lst->len_b] >= lst->max_n)
		{
			push_a(lst);
			if (lst->stack_a[lst->len_a] != lst->max)
				sens = find_sens(lst, lst->max);
			else
			{
				lst->max = find_max(lst->stack_b, lst->len_b);
				lst->max_n = find_next_max(lst->stack_b, lst->len_b, lst->max);
				sens = find_sens_fin(lst);
				if (sens == 0 && lst->len_a > 0
					&& lst->stack_a[0] < lst->stack_a[lst->len_a])
					rrotate_ab(lst);
				else if (lst->len_a > 0
					&& lst->stack_a[0] < lst->stack_a[lst->len_a])
					rrotate_a(lst);
			}
		}
		else
			rotate_final(lst, sens);
		swap_final(lst);
	}
}

static void	split_stack(t_pusw *lst, char sens)
{
	find_pivot(lst);
	sens = find_sens_pivot(lst);
	while (!sort_realstack_a(lst) && lst->len_a != 0)
	{
		if (lst->stack_a[lst->len_a] <= lst->pivot)
		{
			push_b(lst);
			find_pivot(lst);
			sens = find_sens_pivot(lst);
		}
		else if (sens == 0 && lst->len_a < 10 && lst->len_b > 0
			&& lst->stack_b[lst->len_b] < lst->stack_b[0])
			rrotate_ab(lst);
		else if (sens == 0 && lst->len_a < 10)
			rrotate_a(lst);
		else if (lst->len_b > 0
			 && lst->stack_b[lst->len_b] < lst->stack_b[lst->len_b - 1])
			rotate_ab(lst);
		else
			rotate_a(lst);
	}
}

void	ft_algo(t_pusw *lst)
{
	if (!ft_issort(lst))
	{
		if (lst->len_a == 1)
			swap_a(lst);
		else if (lst->len_a == 2)
		{
			swap_final(lst);
			if (lst->stack_a[0] < lst->stack_a[2]
				|| lst->stack_a[0] < lst->stack_a[1])
				rrotate_a(lst);
			swap_final(lst);
		}
		else
		{
			split_stack(lst, 0);
			lst->max = find_max(lst->stack_b, lst->len_b);
			lst->max_n = find_next_max(lst->stack_b, lst->len_b, lst->max);
			push_final(lst, find_sens_fin(lst));
		}
		write(1, lst->buff, lst->count);
	}
}
