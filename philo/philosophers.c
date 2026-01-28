/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:33:14 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/23 16:32:41 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philosopher_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_action(philo, TAKEN_FORK);
	sleep_ms(philo->data->t_die);
	print_action(philo, DIED);
	return ((void *)0);
}

static int	case_one(t_data *data, pthread_t *threads)
{
	data->start_time = get_time();
	if (pthread_create(&threads[0], NULL, philosopher_one, &data->philos[0]))
		return (error(ERR_THREAD_CREATE));
	if (pthread_detach(threads[0]))
		return (error(ERR_THREAD_DETACH));
	sleep_ms(data->t_die + 10);
	free(threads);
	free(data->philos);
	free(data->forks);
	return (EXIT_SUCCESS);
}


int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;

	if (argc < 5 || argc > 6)
		return (error(ERR_INVALID_ARGS));
	if (init_data(&data, argc, argv, &threads))
		return (EXIT_FAILURE);
	if (data.nb_philo == 1)
		return (case_one(&data, threads));
	if (init_philo(&data, threads))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

