/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_rotate.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: dzuntini <dzuntini@student.42nice.fr>		+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/07/06 21:53:04 by dzuntini		   #+#	  #+#			  */
/*   Updated: 2021/07/13 12:48:14 by dzuntini         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_a(t_pusw *lst)
{
	int	len;

	len = lst->len_a;
	if (lst->len_a > 0)
	{
		while (len >= 0)
		{
			lst->stack_a[len + 1] = lst->stack_a[len];
			len--;
		}
		lst->stack_a[0] = lst->stack_a[lst->len_a + 1];
		ft_putbuff(lst, "ra\n", 3);
	}
}

void	rotate_b(t_pusw *lst)
{
	int	len;

	len = lst->len_b;
	if (lst->len_b > 0)
	{
		while (len >= 0)
		{
			lst->stack_b[len + 1] = lst->stack_b[len];
			len--;
		}
		lst->stack_b[0] = lst->stack_b[lst->len_b + 1];
		ft_putbuff(lst, "rb\n", 3);
	}
}

void	rotate_ab(t_pusw *lst)
{
	int	len;

	len = lst->len_a;
	if (lst->len_a > 0)
	{
		while (len >= 0)
		{
			lst->stack_a[len + 1] = lst->stack_a[len];
			len--;
		}
		lst->stack_a[0] = lst->stack_a[lst->len_a + 1];
	}
	len = lst->len_b;
	if (lst->len_b > 0)
	{
		while (len >= 0)
		{
			lst->stack_b[len + 1] = lst->stack_b[len];
			len--;
		}
		lst->stack_b[0] = lst->stack_b[lst->len_b + 1];
	}
	ft_putbuff(lst, "rr\n", 3);
}
