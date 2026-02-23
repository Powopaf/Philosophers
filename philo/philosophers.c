/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:33:14 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/23 09:34:57 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "error/error.h"
#include "init/init.h"
#include "struct.h"
#include "actions/action.h"
#include "utils/utils.h"

static void	*philosopher_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%ld %d %s", get_time() - philo->data->start_time,
		philo->id + 1, TAKEN_FORK);
	sleep_ms(philo->data->t_die);
	printf("%ld %d %s", get_time() - philo->data->start_time,
		philo->id + 1, DIED);
	return ((void *)0);
}

static int	case_one(char *t_die)
{
	pthread_t	thread;
	t_philo		philo;

	philo.data = malloc(sizeof(t_data));
	if (!philo.data)
		return (error(ERR_MALLOC_PHILO));
	philo.id = 0;
	philo.nb_eat = 0;
	philo.last_meal = 0;
	philo.data->t_die = ft_atoi(t_die);
	philo.data->start_time = get_time();
	if (pthread_create(&thread, NULL, philosopher_one, &philo))
		return (error(ERR_THREAD_CREATE));
	pthread_join(thread, NULL);
	free(philo.data);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;

	if (argc < 5 || argc > 6)
		return (error(ERR_INVALID_ARGS));
	if (argv[1][0] == '1' && argv[1][1] == '\0')
		return (case_one(argv[2]));
	if (init_data(&data, argc, argv, &threads))
		return (EXIT_FAILURE);
	if (init_philo(&data, threads))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
