/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:50:57 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/24 12:51:01 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../error/error.h"
#include "../utils/utils.h"
#include "../actions/action.h"
#include "init.h"

static int	cleanup(t_data *data, pthread_t *threads)
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

static int	start_monitors(t_data *data, pthread_t *threads)
{
	if (data->nb_eat > 0)
	{
		if (pthread_create(&threads[data->nb_philo],
				NULL, &monitor2, data) != 0)
			return (error(ERR_THREAD_CREATE));
	}
	else if (pthread_create(&threads[data->nb_philo],
			NULL, &monitor1, data) != 0)
		return (error(ERR_THREAD_CREATE));
	return (EXIT_SUCCESS);
}

int	init_philo(t_data *data, pthread_t *threads)
{
	int	i;

	if (init_start_time(data))
		return (EXIT_FAILURE);
	i = -1;
	if (start_monitors(data, threads))
		return (EXIT_FAILURE);
	while (++i < data->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, &actions, &data->philos[i]) != 0)
			return (error(ERR_THREAD_CREATE));
	}
	if (pthread_join(threads[data->nb_philo], NULL) != 0)
		return (error(ERR_THREAD_JOIN));
	while (i-- > 0)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (error(ERR_THREAD_JOIN));
	}
	return (cleanup(data, threads));
}
