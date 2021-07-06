/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:39:57 by dzuntini          #+#    #+#             */
/*   Updated: 2021/07/06 15:12:16 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_kill(short i, int pid)
{
	int	s;

	usleep(200);
	if (i == 1)
		s = kill(pid, SIGUSR1);
	else if (i == 0)
		s = kill(pid, SIGUSR2);
	else
		s = 0;
	if (s == -1)
	{
		ft_putstr("\nERROR : BAD PID\n");
		exit(-1);
	}
}

void	ft_atob(int a, int pid)
{
	int	mult;
	int	l;

	mult = 128;
	l = 0;
	while (l < 8)
	{
		if (mult <= a)
		{
			ft_kill(1, pid);
			a = a - mult;
		}
		else
			ft_kill(0, pid);
		mult = mult / 2;
		l++;
	}
}

void	ft_sender(char *a, int pid)
{
	int	i;

	i = 0;
	while (a[i] != '\0')
	{
		ft_atob(a[i], pid);
		i++;
	}
	ft_atob('\0', pid);
}

int	ft_atoi(const char *str)
{
	long long int	total;
	int				n;
	int				i;

	total = 0;
	n = 0;
	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		n++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
		total = total * 10 + (str[i++] - '0');
	if (n == 1)
		total = -total;
	return (total);
}

int	main(int ac, char **av)
{
	if (ac != 3)
		ft_putstr("ERROR : Wrong number of arguments");
	else if (ft_number(av[1]) != 0)
		ft_putstr("ERROR : First argument not a number");
	else
	{
		ft_putstr("Sending message :\"");
		ft_putstr(av[2]);
		ft_putstr("\" to : ");
		ft_putstr(av[1]);
		ft_putchar('\n');
		ft_sender(av[2], ft_atoi(av[1]));
	}
}
