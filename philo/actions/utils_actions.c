/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:04:31 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/28 16:04:35 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

void	print_action(t_philo *philo, const char *action)
{
	long	timestamp;

	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->lock);
	if (!philo->data->finished)
		printf("%ld %d %s", timestamp, philo->id + 1, action);
	pthread_mutex_unlock(&philo->data->lock);
}

int	is_finished(t_philo *philo)
{
	int	finished;

	pthread_mutex_lock(&philo->data->lock);
	finished = philo->data->finished;
	pthread_mutex_unlock(&philo->data->lock);
	return (finished);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, SLEEPING);
	sleep_ms(philo->data->t_sleep);
}

void	lock_print_left(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_action(philo, TAKEN_FORK);
}
