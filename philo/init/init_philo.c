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

#include "init.h"

static void	cleanup(t_data *data, pthread_t *threads)
{
	int	i;

	free(data->philos);
	free(data->forks);
	free(threads);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
}

int	init_philo(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	if (data->start_time < 0)
		return (EXIT_FAILURE);
	if (data->nb_eat > 0 && pthread_create(&threads[data->nb_philo], NULL, &monitor2, data) != 0)
		return (error(ERR_THREAD_CREATE));
	else if (pthread_create(&threads[data->nb_philo], NULL, &monitor1, data) != 0)
		return (error(ERR_THREAD_CREATE));
	while (i < data->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, &actions, &data->philos[i]) != 0)
			return (error(ERR_THREAD_CREATE));
		i++;
	}
	while (i-- > 0)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (error(ERR_THREAD_JOIN));
	}
	cleanup(data, threads);
	return (EXIT_SUCCESS);
}
