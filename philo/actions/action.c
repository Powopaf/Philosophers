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

static int	is_finished(t_philo *philo)
{
	int	finished;

	pthread_mutex_lock(&philo->data->lock);
	finished = philo->data->finished;
	pthread_mutex_unlock(&philo->data->lock);
	return (finished);
}

void	print_action(t_philo *philo, const char *action)
{
	long	timestamp;

	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->lock);
	if (!philo->data->finished)
		printf("%ld %d %s", timestamp, philo->id + 1, action);
	pthread_mutex_unlock(&philo->data->lock);
}

static void	eat(t_philo *philo)
{
	print_action(philo, EATING);
	philo->nb_eat++;
	sleep_ms(philo->data->t_eat);
}

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, TAKEN_FORK);
	if (is_finished(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, TAKEN_FORK);
	if (is_finished(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
	eat(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

static void	sleep_and_think(t_philo *philo)
{
	print_action(philo, SLEEPING);
	sleep_ms(philo->data->t_sleep);
}

void *actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_finished(philo))
	{
		print_action(philo, THINKING);
		if (take_forks(philo))
			break;
		if (is_finished(philo))
			break;
		sleep_and_think(philo);
	}
	return ((void *)EXIT_SUCCESS);
}
