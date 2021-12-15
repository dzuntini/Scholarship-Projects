/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:37:11 by dzuntini          #+#    #+#             */
/*   Updated: 2021/11/18 09:37:12 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ribool	ph_exit(t_ribool error, const char *str, t_assembly *assembly)
{
	t_philo	*philo;
	int		crnt_philo;

	if (error)
		printf("Error : %s\n", str);
	philo = assembly->philos;
	if (philo)
	{
		crnt_philo = -1;
		while (++crnt_philo < assembly->exit_nb_philo)
		{
			pthread_mutex_unlock(&(philo->fork));
			pthread_mutex_destroy(&(philo->fork));
			philo = philo->next;
		}
		pthread_mutex_unlock(&(assembly->creation));
		pthread_mutex_destroy(&(assembly->creation));
		pthread_mutex_unlock(&(assembly->digest));
		pthread_mutex_destroy(&(assembly->digest));
		pthread_mutex_unlock(&(assembly->actions));
		pthread_mutex_destroy(&(assembly->actions));
	}
	return (T_FALSE);
}

static void	*ph_death_checker(void *assembly)
{
	unsigned long	crnt_ms_time;
	t_assembly		*asses;
	t_philo			*philo;

	asses = (t_assembly *)assembly;
	philo = asses->philos;
	while (asses->nb_philos)
	{
		crnt_ms_time = ph_wait_time(0);
		if (crnt_ms_time > (philo->last_lunch + asses->time_to_die))
		{
			asses->nb_philos = 0;
			pthread_mutex_lock(&(asses->actions));
			printf("%lu ms %s died\n", crnt_ms_time - asses->start,
				asses->philos->name);
			pthread_mutex_unlock(&(asses->creation));
			return (NULL);
		}
		philo = philo->next;
	}
	pthread_mutex_unlock(&(asses->creation));
	return (NULL);
}

static t_ribool	ph_create_philosophers(t_assembly *assembly)
{
	int		current;
	t_philo	*new_philo;
	t_philo	*first;

	current = 0;
	pthread_mutex_lock(&(assembly->creation));
	while (current++ < assembly->nb_philos)
	{
		new_philo = (t_philo *)malloc(sizeof(t_philo));
		if (!new_philo || !(ph_itoa(current, new_philo)))
			return (ph_exit(T_TRUE, ERROR_MEMORY, assembly));
		if (!(ph_init_mutex(new_philo, assembly, T_TRUE)))
			return (T_FALSE);
		new_philo->id = (current % 2);
		if (!(assembly->philos))
		{
			first = new_philo;
			assembly->philos = new_philo;
		}
		assembly->philos->next = new_philo;
		assembly->philos = new_philo;
	}
	new_philo->next = first;
	assembly->philos = new_philo->next;
	return (T_TRUE);
}

static t_ribool	ph_init(t_assembly *assembly, char **av, int ac)
{
	assembly->philos = NULL;
	if (ac < 5 || ac > 6)
		return (ph_exit(T_TRUE, ERROR_PARAM_QTTY, assembly));
	if (!ph_isnum(av[1]) || !ph_isnum(av[2]) || !ph_isnum(av[3])
		|| !ph_isnum(av[4]) || (ac == 6 && !ph_isnum(av[5])))
		return (ph_exit(T_TRUE, ERROR_PARAM_TYPE, assembly));
	assembly->ac = ac;
	assembly->nb_philos = ph_atoi(av[1]);
	assembly->exit_nb_philo = assembly->nb_philos;
	if (assembly->nb_philos < 1 || assembly->nb_philos > 200)
		return (ph_exit(T_TRUE, ERROR_PARAM_VALUE, assembly));
	(assembly->time_to_die) = ph_atoi(av[2]);
	(assembly->time_to_eat) = ph_atoi(av[3]);
	(assembly->time_to_sleep) = ph_atoi(av[4]);
	assembly->nb_meals = -1;
	if (assembly->ac == 6)
		assembly->nb_meals = ph_atoi(av[5]);
	assembly->philos = NULL;
	if (!(ph_create_philosophers(assembly)))
		return (T_FALSE);
	return (ph_init_mutex(NULL, assembly, T_FALSE));
}

int	main(int ac, char **av)
{
	t_assembly		asmbly;
	t_philo			*philo;
	pthread_t		death;
	int				crnt_philo;

	if (!(ph_init(&asmbly, av, ac)))
		return (T_FALSE);
	philo = asmbly.philos;
	crnt_philo = -1;
	asmbly.start = ph_wait_time(0);
	while (++crnt_philo < (asmbly.nb_philos))
	{
		pthread_mutex_lock(&(asmbly.creation));
		if (asmbly.philos->id)
			pthread_create(&(asmbly.philos->life), NULL, ph_odd_live, &asmbly);
		else
			pthread_create(&(asmbly.philos->life), NULL, ph_pair_live, &asmbly);
	}
	pthread_mutex_lock(&(asmbly.creation));
	pthread_create(&death, NULL, ph_death_checker, &asmbly);
	pthread_mutex_lock(&(asmbly.creation));
	pthread_mutex_unlock(&(asmbly.creation));
	pthread_join(death, NULL);
	pthread_mutex_lock(&(asmbly.creation));
	return (ph_exit(T_FALSE, NULL, &asmbly));
}
