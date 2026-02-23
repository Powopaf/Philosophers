/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:50:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/23 09:36:14 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "../utils/utils.h"
#include "action.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = get_time();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->lock);
	print_action(philo, EATING);
	sleep_ms(philo->data->t_eat);
}

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, TAKEN_FORK);
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, TAKEN_FORK);
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, TAKEN_FORK);
	}
	if (is_finished(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	eat(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_finished(philo))
	{
		print_action(philo, THINKING);
		if (take_forks(philo))
			break ;
		if (is_finished(philo))
			break ;
		sleeping(philo);
	}
	return ((void *)EXIT_SUCCESS);
}
