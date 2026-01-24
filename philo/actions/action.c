/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:50:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/24 12:50:43 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

void	print_action(t_philo *philo, const char *action)
{
	long	timestamp;

	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d %s\n", timestamp, philo->id + 1, action);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static void	eat(t_philo *philo)
{
	print_action(philo, EATING);
	philo->nb_eat++;
	sleep_ms(philo->data->t_eat);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, TAKEN_FORK);
	eat(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	sleep_and_think(t_philo *philo)
{
	print_action(philo, SLEEPING);
	sleep_ms(philo->data->t_sleep);
}

void *actions(void *arg)
{
	t_philo	*philo;
	int i = 0;

	philo = (t_philo *)arg;
	while (i < philo->data->nb_eat || philo->data->nb_eat == -1)
	{
		print_action(philo, THINKING);
		take_forks(philo);
		sleep_and_think(philo);
		i++;
	}
	return ((void *)EXIT_SUCCESS);
}
