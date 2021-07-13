/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 19:20:45 by dzuntini          #+#    #+#             */
/*   Updated: 2021/07/13 12:51:50 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_init(int ac, char **av, int m)
{
	t_pusw	*lst;

	ft_check(ac, av, m);
	lst = NULL;
	lst = malloc(sizeof(t_pusw));
	if (!(lst))
		ft_error();
	lst->len_b = -1;
	lst->stack_a = malloc(ac * sizeof(int));
	lst->stack_b = malloc(ac * sizeof(int));
	if ((!(lst->stack_a)) || (!(lst->stack_b)))
		ft_error();
	while (--ac >= 0)
		lst->stack_a[lst->len_a++] = ft_atoi(av[ac]);
	lst->len_a--;
	if (m)
		ft_freetab(av);
	else
		lst->len_a--;
	ft_algo(lst);
	ft_freelst(lst);
}

int	main(int ac, char **av)
{
	int	i;

	if (ac == 2)
	{
		i = 0;
		av = ft_split(av[1], ' ');
		while (av[i] != NULL)
			i++;
		ft_init(i, av, 1);
	}
	else if (ac > 1)
		ft_init(ac, av, 0);
	return (0);
}
