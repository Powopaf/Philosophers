/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:06:13 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 11:44:32 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "init.h"

void	clean_mutexes(t_data *data, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	i = 0;
	free(data->philos);
	free(data->forks);
}

void	clean_forks(t_data *data, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	clean_mutexes(data, data->nb_philo);
}
