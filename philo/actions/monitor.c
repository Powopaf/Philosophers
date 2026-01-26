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
	if (get_time() - philo->last_meal > philo->data->t_die)
		return (1);
	return (0);
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
				print_action(&data->philos[i], DIED);
				return ((void *)0);
			}
			i++;
		}
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
			if (data->philos[i].nb_eat < data->nb_eat)
				all_ate = 0;
			
			if (check_death(&data->philos[i]))
			{
				print_action(&data->philos[i], DIED);
				data->finished = 1;
				return ((void *)0);
			}
			i++;
		}
		if (all_ate)
			return ((void *)0);
	}
	return ((void *)1);
}
