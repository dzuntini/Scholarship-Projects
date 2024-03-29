/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:33:25 by pcarella          #+#    #+#             */
/*   Updated: 2021/09/23 14:30:54 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	toolong_exit(const char *str, long long *nb)
{
	int					sign;
	unsigned long long	num;

	sign = 1;
	num = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		num = (num * 10) + (*str - 48);
		if ((sign < 0 && num > ((unsigned long long)LLONG_MAX + 1))
			|| (sign > 0 && num > LLONG_MAX))
			return (0);
		str++;
	}
	*nb = num * sign;
	return (1);
}

int	error_exit(char **param)
{
	long long	ret;

	ret = toolong_exit(param[0], &ret);
	if (ret == 0 || ft_str_isdigit(param[0]) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(param[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (255);
	}
	else if (ft_tablen((void **)param) > 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	builtin_exit(t_data *ms, char **param)
{
	(void)ms;
	if (ft_tablen((void **)param) > 0)
	{
		if (error_exit(param) == 1)
			return (1);
		else if (ft_str_isdigit(param[0]) == 1 && !param[1])
			exit (ft_atoi(param[0]));
	}
	exit (0);
}
