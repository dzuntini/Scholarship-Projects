/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_rrotate.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: dzuntini <dzuntini@student.42nice.fr>		+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/07/06 21:47:07 by dzuntini		   #+#	  #+#			  */
/*   Updated: 2021/07/13 12:49:50 by dzuntini         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "push_swap.h"
void	rrotate_a(t_pusw *lst)
{
	int	len;

	len = 0;
	if (lst->len_a > 0)
	{
		lst->stack_a[lst->len_a + 1] = lst->stack_a[0];
		while (len < (lst->len_a + 1))
		{
			lst->stack_a[len] = lst->stack_a[len + 1];
			len++;
		}
		ft_putbuff(lst, "rra\n", 4);
	}
}

void	rrotate_b(t_pusw *lst)
{
	int	len;

	len = 0;
	if (lst->len_b > 0)
	{
		lst->stack_b[lst->len_b + 1] = lst->stack_b[0];
		while (len < (lst->len_b + 1))
		{
			lst->stack_b[len] = lst->stack_b[len + 1];
			len++;
		}
		ft_putbuff(lst, "rrb\n", 4);
	}
}

void	rrotate_ab(t_pusw *lst)
{
	int	len;

	len = 0;
	if (lst->len_b > 0)
	{
		lst->stack_b[lst->len_b + 1] = lst->stack_b[0];
		while (len < (lst->len_b + 1))
		{
			lst->stack_b[len] = lst->stack_b[len + 1];
			len++;
		}
	}
	len = 0;
	if (lst->len_a > 0)
	{
		lst->stack_a[lst->len_a + 1] = lst->stack_a[0];
		while (len < (lst->len_a + 1))
		{
			lst->stack_a[len] = lst->stack_a[len + 1];
			len++;
		}
	}
	ft_putbuff(lst, "rrr\n", 4);
}
