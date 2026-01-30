/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:37:15 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/28 14:01:58 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "action.h"
#include "../utils/utils.h"

static int	check_death(t_philo *philo)
{
	long	last_meal;
	int		result;

	pthread_mutex_lock(&philo->lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->lock);
	if (get_time() - last_meal > philo->data->t_die)
		result = 1;
	else
		result = 0;
	return (result);
}

void	*monitor1(void *arg)
{
	t_data	*data;
	int		i;
	long	timestamp;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_death(&data->philos[i]))
			{
				pthread_mutex_lock(&data->lock);
				data->finished = 1;
				timestamp = get_time() - data->start_time;
				printf("%ld %d died\n", timestamp, data->philos[i].id + 1);
				pthread_mutex_unlock(&data->lock);
				return ((void *)0);
			}
			i++;
		}
		usleep(10);
	}
	return ((void *)1);
}

static void	lock_finish(t_data *data, int i)
{
	pthread_mutex_lock(&data->lock);
	data->finished = 1;
	pthread_mutex_unlock(&data->lock);
	if (i >= 0)
		printf("%ld %d died\n", get_time()
			- data->start_time, data->philos[i].id + 1);
}

void	*monitor2(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		all_ate = 1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philos[i].lock);
			if (data->philos[i].nb_eat < data->nb_eat)
				all_ate = 0;
			pthread_mutex_unlock(&data->philos[i].lock);
			if (check_death(&data->philos[i]))
			{
				return (lock_finish(data, i), (void *)0);
			}
		}
		if (all_ate)
			return (lock_finish(data, -1), (void *)0);
		usleep(10);
	}
	return ((void *)1);
}
