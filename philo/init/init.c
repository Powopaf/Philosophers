/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:07:00 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/28 14:00:34 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static	int	init_first_philo(t_data *data)
{
	data->philos[0].id = 0;
	data->philos[0].nb_eat = 0;
	data->philos[0].data = data;
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->nb_philo - 1];
	if (pthread_mutex_init(&data->philos[0].lock, NULL) != 0)
		return (error(ERR_MUTEX_INIT));
	return (EXIT_SUCCESS);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (error(ERR_MALLOC_PHILO));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (error(ERR_MALLOC_FORKS));
	if (init_first_philo(data) != 0)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].nb_eat = 0;
		data->philos[i].data = data;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		if (pthread_mutex_init(&data->philos[i].lock, NULL) != 0)
			return (error(ERR_MUTEX_INIT));
	}
	return (EXIT_SUCCESS);
}

static int	check(t_data *data)
{
	if (data->nb_philo <= 0)
		return (EXIT_FAILURE);
	if (data->t_eat < 0)
		return (EXIT_FAILURE);
	if (data->t_sleep < 0)
		return (EXIT_FAILURE);
	if (data->t_die < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_forks(t_data *data, pthread_t **threads)
{
	int	i;

	*threads = malloc(sizeof(pthread_t) * (data->nb_philo + 1));
	if (!*threads)
		return (error(ERR_MALLOC_THREADS));
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error(ERR_MUTEX_INIT));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, int argc, char **argv, pthread_t **threads)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->finished = 0;
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	if (check(data))
		return (EXIT_FAILURE);
	if (init_philos(data))
		return (EXIT_FAILURE);
	if (init_forks(data, threads))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (error(ERR_MUTEX_INIT));
	return (EXIT_SUCCESS);
}
