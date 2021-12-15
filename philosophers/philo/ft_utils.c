/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:35:43 by dzuntini          #+#    #+#             */
/*   Updated: 2021/11/18 09:35:44 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ph_wait_time(unsigned int ms_wait)
{
	struct timeval	crnt_time;
	unsigned long	start_wait;

	gettimeofday(&(crnt_time), NULL);
	start_wait = ((crnt_time.tv_sec) * 1000) + ((crnt_time.tv_usec) / 1000);
	if (!ms_wait)
		return (start_wait);
	while (ms_wait > (ph_wait_time(0) - start_wait))
		usleep(ms_wait);
	gettimeofday(&(crnt_time), NULL);
	return (((crnt_time.tv_sec) * 1000) + ((crnt_time.tv_usec) / 1000));
}

t_ribool	ph_init_mutex(t_philo *philo, t_assembly *assembly, t_ribool fork)
{
	if (fork)
	{
		philo->nb_meals = assembly->nb_meals;
		if (!(pthread_mutex_init(&(philo->fork), NULL)))
			return (T_TRUE);
		free(philo->name);
		philo->name = NULL;
		free(philo);
	}
	else if (!(pthread_mutex_init(&(assembly->creation), NULL)))
	{
		if (!(pthread_mutex_init(&(assembly->actions), NULL)))
		{
			if (!(pthread_mutex_init(&(assembly->digest), NULL)))
				return (T_TRUE);
			pthread_mutex_destroy(&(assembly->actions));
		}
		pthread_mutex_destroy(&(assembly->creation));
	}
	return (ph_exit(T_TRUE, ERROR_MUTEX_INIT, assembly));
}

t_ribool	ph_itoa(int n, t_philo *new_philo)
{
	int	n_cpy;
	int	len;

	n_cpy = n;
	len = 0;
	while (n_cpy && ++len)
		n_cpy /= 10;
	new_philo->name = (char *)malloc(sizeof(len));
	if (!(new_philo->name))
	{
		free(new_philo);
		return (T_FALSE);
	}
	(new_philo->name)[len] = '\0';
	while (len--)
	{
		(new_philo->name)[len] = (n % 10) + '0';
		n /= 10;
	}
	return (T_TRUE);
}

int	ph_atoi(const char *str)
{
	int	nbr;

	nbr = 0;
	while (*str)
		nbr = (nbr * 10) + (*(str++) - '0');
	return (nbr);
}

t_ribool	ph_isnum(const char *str)
{
	while (*str)
		if (*str < '0' || *(str++) > '9')
			return (T_FALSE);
	return (T_TRUE);
}
