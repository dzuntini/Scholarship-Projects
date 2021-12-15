/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_begin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:35:28 by dzuntini          #+#    #+#             */
/*   Updated: 2021/11/18 09:35:29 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_philosophers_live_init(t_philo **philo,
	t_assembly *assembly, t_assembly **asses)
{
	(*asses) = ((t_assembly *)assembly);
	(*philo) = ((*asses)->philos);
	((*asses)->philos) = (*asses)->philos->next;
	((*philo)->last_lunch) = ph_wait_time(0);
	pthread_mutex_unlock(&((*asses)->creation));
}

static void	ph_philosopher_digest(t_philo *philo, t_assembly *assembly)
{
	if (philo->nb_meals > 0 && !(--(philo->nb_meals)))
	{
		if (assembly->nb_philos)
		{
			pthread_mutex_lock(&(assembly->digest));
			(assembly->nb_philos)--;
		}
		if (assembly->nb_philos)
			pthread_mutex_unlock(&(assembly->digest));
	}
}

static void	ph_philosopher_action(t_assembly *assembly,
	t_philo *philo, unsigned int ms_time, char *action)
{
	if (assembly->nb_philos)
		pthread_mutex_lock(&(assembly->actions));
	if (assembly->nb_philos)
		printf("%lu ms %s is %s\n", (ph_wait_time(0) - assembly->start),
			philo->name, action);
	if (assembly->nb_philos)
		pthread_mutex_unlock(&(assembly->actions));
	ph_wait_time(ms_time);
}

void	*ph_pair_live(void *assembly)
{
	t_assembly		*asses;
	t_philo			*philo;

	ph_philosophers_live_init(&philo, (t_assembly *)assembly, &asses);
	while (asses->nb_philos)
	{
		if (asses->nb_philos)
			pthread_mutex_lock(&(philo->fork));
		ph_philosopher_action(asses, philo, 0, "taking left fork");
		if (asses->nb_philos)
			pthread_mutex_lock(&(philo->next->fork));
		ph_philosopher_action(asses, philo, 0, "taking right fork");
		(philo->last_lunch) = ph_wait_time(0);
		ph_philosopher_action(asses, philo, asses->time_to_eat, "eating");
		ph_philosopher_digest(philo, asses);
		if (asses->nb_philos)
			pthread_mutex_unlock(&(philo->fork));
		if (asses->nb_philos)
			pthread_mutex_unlock(&(philo->next->fork));
		ph_philosopher_action(asses, philo, asses->time_to_sleep, "sleeping");
		ph_philosopher_action(asses, philo, 0, "thinking");
	}
	return (NULL);
}

void	*ph_odd_live(void *assembly)
{
	t_assembly		*asses;
	t_philo			*philo;

	ph_philosophers_live_init(&philo, (t_assembly *)assembly, &asses);
	while (asses->nb_philos)
	{	
		if (asses->nb_philos)
			pthread_mutex_lock(&(philo->next->fork));
		ph_philosopher_action(asses, philo, 0, "taking right fork");
		if (asses->nb_philos)
			pthread_mutex_lock(&(philo->fork));
		ph_philosopher_action(asses, philo, 0, "taking left fork");
		(philo->last_lunch) = ph_wait_time(0);
		ph_philosopher_action(asses, philo, asses->time_to_eat, "eating");
		ph_philosopher_digest(philo, asses);
		if (asses->nb_philos)
			pthread_mutex_unlock(&(philo->next->fork));
		if (asses->nb_philos)
			pthread_mutex_unlock(&(philo->fork));
		ph_philosopher_action(asses, philo, asses->time_to_sleep, "sleeping");
		ph_philosopher_action(asses, philo, 0, "thinking");
	}
	return (NULL);
}
