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

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &actions, &data->philos[i]) != 0)
			return (error(ERR_THREAD_CREATE));
		i++;
	}
	while (i-- > 0)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (error(ERR_THREAD_JOIN));
	}
	return (EXIT_SUCCESS);
}
