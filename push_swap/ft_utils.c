/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_utils.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: dzuntini <dzuntini@student.42nice.fr>		+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/07/06 19:04:45 by dzuntini		   #+#	  #+#			  */
/*   Updated: 2021/07/13 12:51:07 by dzuntini         ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_issort(t_pusw *lst)
{
	int	count;

	count = lst->len_a;
	if (lst->len_b != -1)
		return (0);
	while (count > 0)
	{
		if (!(lst->stack_a[count] < lst->stack_a[count - 1]))
			return (0);
		count--;
	}
	return (1);
}

void	ft_error(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(-1);
}

void	ft_putbuff(t_pusw *lst, char *str, char len)
{
	if ((lst->count + len) > BUFFSIZE)
	{
		write(1, lst->buff, lst->count);
		lst->count = 0;
	}
	ft_memcpy(lst->buff + lst->count, str, len);
	lst->count += len;
}

void	ft_freelst(t_pusw *lst)
{
	free(lst->stack_a);
	free(lst->stack_b);
	free(lst);
	exit(0);
}
