/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 algo1.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: dzuntini <dzuntini@student.42nice.fr>		+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/07/06 22:48:40 by dzuntini		   #+#	  #+#			  */
/*   Updated: 2021/07/13 12:44:58 by dzuntini         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_final(t_pusw *lst, char sens)
{
	if (sens == 1 && lst->len_a > 0
		&& lst->stack_a[lst->len_a] == lst->max_n)
		rotate_ab(lst);
	else if (sens == 1)
		rotate_b(lst);
	else if (sens == 0 && lst->len_a > 0
		&& lst->stack_a[0] < lst->stack_a[lst->len_a])
		rrotate_ab(lst);
	else
		rrotate_b(lst);
}

int	sort_stack_a(t_pusw *lst)
{
	int	len;

	len = lst->len_a;
	while (len > 0)
	{
		if (lst->stack_a[len] > lst->stack_a[len - 1])
			return (0);
		len--;
	}
	return (1);
}

int	sort_realstack_a(t_pusw *lst)
{
	if ((find_min(lst->stack_a, lst->len_a)
			> find_max(lst->stack_b, lst->len_b)) && sort_stack_a(lst))
		return (1);
	return (0);
}
