/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:36:08 by dzuntini          #+#    #+#             */
/*   Updated: 2021/11/18 09:36:09 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR_PARAM_QTTY "philo requires five or six parameters"
# define ERROR_PARAM_TYPE "philo requires only unsigned \
positive number parameters"
# define ERROR_PARAM_VALUE "number of philosophers must be between 1 and 200"
# define ERROR_MEMORY "no memory found to load"
# define ERROR_MUTEX_INIT "initialization failed"

typedef enum e_ribool
{
	T_FALSE,
	T_TRUE,
	T_MAYBE
}				t_ribool;

typedef enum e_flow
{
	OUT,
	IN
}				t_flow;

typedef struct s_philo	t_philo;

struct s_philo
{
	pthread_t		life;
	int				id;
	unsigned long	last_lunch;
	char			*name;
	pthread_mutex_t	fork;
	int				nb_meals;
	t_philo			*next;
};

typedef struct s_assembly
{
	pthread_mutex_t	creation;
	pthread_mutex_t	actions;
	pthread_mutex_t	digest;		
	int				ac;
	int				nb_philos;
	int				exit_nb_philo;
	unsigned long	start;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_die;
	int				nb_meals;
	t_ribool		end;
	t_philo			*philos;
}				t_assembly;

t_ribool		ph_exit(t_ribool error, const char *str, t_assembly *assembly);

unsigned long	ph_wait_time(unsigned int ms_wait);
t_ribool		ph_init_mutex(t_philo *philo,
					t_assembly *assembly, t_ribool fork);
t_ribool		ph_itoa(int n, t_philo *new);
int				ph_atoi(const char *str);
t_ribool		ph_isnum(const char *str);

void			*ph_odd_live(void *assembly);
void			*ph_pair_live(void *assembly);

#endif
