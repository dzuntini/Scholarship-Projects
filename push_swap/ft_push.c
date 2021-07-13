/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_push.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: dzuntini <dzuntini@student.42nice.fr>		+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/07/06 21:42:48 by dzuntini		   #+#	  #+#			  */
/*   Updated: 2021/07/13 12:47:25 by dzuntini         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "push_swap.h"

void	push_a(t_pusw *lst)
{
	if (lst->len_b >= 0)
	{
		lst->stack_a[++lst->len_a] = lst->stack_b[lst->len_b--];
		ft_putbuff(lst, "pa\n", 3);
	}
}

void	push_b(t_pusw *lst)
{
	if (lst->len_a >= 0)
	{
		lst->stack_b[++lst->len_b] = lst->stack_a[lst->len_a--];
		ft_putbuff(lst, "pb\n", 3);
	}
}
