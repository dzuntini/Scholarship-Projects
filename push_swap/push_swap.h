/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:55:49 by dzuntini          #+#    #+#             */
/*   Updated: 2021/07/08 20:59:17 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <stdio.h>

# define BUFFSIZE 10

typedef struct s_pusw
{
	int		*stack_a;
	int		len_a;
	int		*stack_b;
	int		len_b;
	int		pivot;
	int		max;
	int		max_n;
	char	buff[BUFFSIZE];
	int		count;
}				t_pusw;

/*---------------------------------
**			ft_algo.c
**--------------------------------
*/
void	ft_algo(t_pusw *lst);
void	rotate_final(t_pusw *lst, char sens);
int		sort_stack_a(t_pusw *lst);
int		sort_realstack_a(t_pusw *lst);
/*---------------------------------
**			ft_push.c
**--------------------------------
*/
void	push_a(t_pusw *lst);
void	push_b(t_pusw *lst);
/*---------------------------------
**			ft_rotate.c
**--------------------------------
*/
void	rotate_a(t_pusw *lst);
void	rotate_b(t_pusw *lst);
void	rotate_ab(t_pusw *lst);
/*---------------------------------
**			ft_rrotate.c
**--------------------------------
*/
void	rrotate_a(t_pusw *lst);
void	rrotate_b(t_pusw *lst);
void	rrotate_ab(t_pusw *lst);
/*---------------------------------
**			ft_swap.c
**--------------------------------
*/
void	swap_final(t_pusw *lst);
void	swap_a(t_pusw *lst);
void	swap_b(t_pusw *lst);
void	swap_ab(t_pusw *lst);
/*---------------------------------
**			ft_checker.c
**--------------------------------
*/
int		ft_ordercheck(int *list, int lim);
int		ft_check(int ac, char **av, int m);
/*---------------------------------
**			ft_nbrfind.c
**--------------------------------
*/
int		find_min(int *stack, int len);
int		find_max(int *stack, int len);
int		find_next_min(int *stack, int len, int tmp);
int		find_next_max(int *stack, int len, int tmp);
int		find_nb(int *stack, int len, int nb);
/*---------------------------------
**			ft_utils.c
**--------------------------------
*/
void	ft_error(void);
void	ft_freelst(t_pusw *lst);
void	ft_putbuff(t_pusw *lst, char *str, char len);
int		ft_issort(t_pusw *lst);
/*
**
*/
void	find_pivot(t_pusw *lst);
int		find_sens_fin(t_pusw *lst);
int		find_sens_pivot(t_pusw *lst);
int		find_sens(t_pusw *lst, int max);
int		sort_stack_a(t_pusw *lst);
int		sort_realstack_a(t_pusw *lst);
#endif
