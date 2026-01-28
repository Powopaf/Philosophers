/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:37:15 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/24 15:37:17 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"

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
				pthread_mutex_unlock(&data->lock);
				print_action(&data->philos[i], DIED);
				return ((void *)0);
			}
			i++;
		}
		usleep(5);
	}
	return ((void *)1);
}

void	*monitor2(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		all_ate = 1;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philos[i].lock);
			if (data->philos[i].nb_eat < data->nb_eat)
				all_ate = 0;
			pthread_mutex_unlock(&data->philos[i].lock);
			
			if (check_death(&data->philos[i]))
			{
				print_action(&data->philos[i], DIED);
				pthread_mutex_lock(&data->lock);
				data->finished = 1;
				pthread_mutex_unlock(&data->lock);
				return ((void *)0);
			}
			i++;
		}
		if (all_ate)
		{
			pthread_mutex_lock(&data->lock);
			data->finished = 1;
			pthread_mutex_unlock(&data->lock);
			return ((void *)0);
		}
		usleep(5);
	}
	return ((void *)1);
}
