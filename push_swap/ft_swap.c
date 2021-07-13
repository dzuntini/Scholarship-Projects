/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_swap.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: dzuntini <dzuntini@student.42nice.fr>		+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/07/06 20:55:30 by dzuntini		   #+#	  #+#			  */
/*   Updated: 2021/07/13 12:50:44 by dzuntini         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_final(t_pusw *lst)
{
	if (lst->len_a > 0 && lst->len_b > 0
		&& lst->stack_a[lst->len_a] > lst->stack_a[lst->len_a - 1]
		&& lst->stack_b[lst->len_b] < lst->stack_b[lst->len_b - 1])
		swap_ab(lst);
	else if (lst->len_a > 0
		&& lst->stack_a[lst->len_a] > lst->stack_a[lst->len_a - 1])
		swap_a(lst);
}

void	swap_a(t_pusw *lst)
{
	int	swap;

	if (lst->len_a > 0)
	{
		swap = lst->stack_a[lst->len_a];
		lst->stack_a[lst->len_a] = lst->stack_a[lst->len_a - 1];
		lst->stack_a[lst->len_a - 1] = swap;
		ft_putbuff(lst, "sa\n", 3);
	}
}

void	swap_b(t_pusw *lst)
{
	int	swap;

	if (lst->len_b > 0)
	{
		swap = lst->stack_b[lst->len_b];
		lst->stack_b[lst->len_b] = lst->stack_b[lst->len_b - 1];
		lst->stack_b[lst->len_b - 1] = swap;
		ft_putbuff(lst, "sb\n", 3);
	}
}

void	swap_ab(t_pusw *lst)
{
	int	swap;

	if (lst->len_a > 0 || lst->len_b > 0)
	{
		if (lst->len_a > 0)
		{
			swap = lst->stack_a[lst->len_a];
			lst->stack_a[lst->len_a] = lst->stack_a[lst->len_a - 1];
			lst->stack_a[lst->len_a - 1] = swap;
		}
		if (lst->len_b > 0)
		{
			swap = lst->stack_b[lst->len_b];
			lst->stack_b[lst->len_b] = lst->stack_b[lst->len_b - 1];
			lst->stack_b[lst->len_b - 1] = swap;
		}
		ft_putbuff(lst, "ss\n", 3);
	}
}
