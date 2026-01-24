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
	if (get_time() - philo->data->start_time > philo->data->t_die)
		return (1);
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo->data->nb_philo)
		{
			if (check_death(&philo[i]))
			{
				print_action(&philo[i], DIED);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
