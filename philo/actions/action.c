/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:50:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/28 14:01:32 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "../utils/utils.h"
#include "action.h"

static void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
}

static void	eat(t_philo *philo)
{
	print_action(philo, EATING);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 1;
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->lock);
	sleep_ms(philo->data->t_eat);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

/*
** Philosopher takes the forks. To avoid deadlock, the last philosopher
** takes the right fork first.
** Returns 1 if the simulation is finished, 0 otherwise.
** The code in if and else is almost the same I recommend to refactor it.
** use a pointer to function ?
*/

static int	take_forks(t_philo *philo)
{
	if (philo->id == philo->data->nb_philo - 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, TAKEN_FORK);
		if (is_finished(philo))
			return (pthread_mutex_unlock(philo->r_fork), 1);
		lock_print_left(philo);
		if (is_finished(philo))
			return (unlock_forks(philo), 1);
	}
	else
	{
		lock_print_left(philo);
		if (is_finished(philo))
			return (pthread_mutex_unlock(philo->l_fork), 1);
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, TAKEN_FORK);
		if (is_finished(philo))
			return (unlock_forks(philo), 1);
	}
	return (EXIT_SUCCESS);
}

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_finished(philo))
	{
		print_action(philo, THINKING);
		if (take_forks(philo))
			break ;
		if (is_finished(philo))
			break ;
		if (!is_finished(philo))
			eat(philo);
		set_last_meal(philo);
		unlock_forks(philo);
		if (is_finished(philo))
			break ;
		sleeping(philo);
	}
	return ((void *)EXIT_SUCCESS);
}
