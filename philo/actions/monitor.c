/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:37:15 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/23 11:29:42 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "action.h"
#include "../utils/utils.h"

static int	check_death(t_philo *philo)
{
	return (get_time() - philo->last_meal > philo->data->t_die);
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
		usleep(1000);
	}
	return ((void *)1);
}

static void	lock_finish(t_data *data, int i)
{
	pthread_mutex_lock(&data->lock);
	data->finished = 1;
	if (i >= 0)
		printf("%ld %d died\n", get_time()
			- data->start_time, data->philos[i].id + 1);
	pthread_mutex_unlock(&data->lock);
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
			if (data->philos[i].nb_eat < data->nb_eat)
				all_ate = 0;
			if (check_death(&data->philos[i]))
			{
				return (lock_finish(data, i), (void *)0);
			}
		}
		if (all_ate)
			return (lock_finish(data, -1), (void *)0);
		usleep(1000);
	}
	return ((void *)1);
}
