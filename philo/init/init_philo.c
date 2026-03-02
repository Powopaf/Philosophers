/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:50:57 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 10:04:19 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../error/error.h"
#include "../utils/utils.h"
#include "../actions/action.h"
#include "init.h"

int	cleanup(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	free(data->philos);
	free(data->forks);
	free(threads);
	return (EXIT_SUCCESS);
}

static int	init_start_time(t_data *data)
{
	int	i;

	data->start_time = get_time();
	if (data->start_time < 0)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	wait_threads(pthread_t *threads, int i)
{
	while (i >= 0)
	{
		pthread_join(threads[i], NULL);
		i--;
	}
}

static int	start_monitor(t_data *data, pthread_t *threads)
{
	pthread_t	monitor_thread;

	if (data->nb_eat < 0)
	{
		if (pthread_create(&monitor_thread, NULL, monitor1, data))
		{
			wait_threads(threads, data->nb_philo - 1);
			error(ERR_THREAD_CREATE);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (pthread_create(&monitor_thread, NULL, monitor2, data))
		{
			wait_threads(threads, data->nb_philo - 1);
			error(ERR_THREAD_CREATE);
			return (EXIT_FAILURE);
		}
	}
	pthread_join(monitor_thread, NULL);
	return (EXIT_SUCCESS);
}

int	init_philo(t_data *data, pthread_t *threads)
{
	int	i;

	if (init_start_time(data))
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, actions, &data->philos[i]))
			return (wait_threads(threads, i - 1), error(ERR_THREAD_CREATE));
		i++;
	}
	if (start_monitor(data, threads))
		return (EXIT_FAILURE);
	wait_threads(threads, i - 1);
	return (cleanup(data, threads));
}
