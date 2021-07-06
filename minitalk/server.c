/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 11:41:57 by dzuntini          #+#    #+#             */
/*   Updated: 2021/07/06 15:26:51 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_receive(short i)
{
	static short	l = 0;
	static char		b = 0;
	static int		mult = 128;

	if (i == -1)
		l = 8;
	b += (i * mult);
	mult = mult / 2;
	l++;
	if (l >= 8)
	{
		if (i != -1)
			ft_putchar(b);
		if (b == 0)
			ft_putchar('\n');
		b = 0;
		l = 0;
		mult = 128;
	}
}

void	sig_handler(int signo, siginfo_t *t, void *c)
{
	static int	pid = 0;

	(void)c;
	if (t->si_pid && (signo == SIGUSR1 || signo == SIGUSR2))
	{
		if (pid != t->si_pid)
			ft_receive(-1);
		pid = t->si_pid;
	}
	if (signo == SIGUSR1)
		ft_receive(1);
	if (signo == SIGUSR2)
		ft_receive(0);
}

void	booting(int pid)
{
	int	i;

	i = 0;
	ft_putstr("Windows MEH booting up");
	while (i < 5)
	{
		ft_putchar('.');
		usleep(500000);
		i++;
	}
	ft_putstr("Error : Server launched successfully\n");
	ft_putstr("\nServer Up , Pid is :");
	ft_putnbr(pid);
	ft_putchar('\n');
}

int	main(void)
{
	struct sigaction	sa;	
	sigset_t			block_mask;
	int					pid;

	pid = getpid();
	booting(pid);
	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = block_mask;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (42)
		pause();
}
