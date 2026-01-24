/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:50:42 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/24 12:50:43 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "action.h"



void *actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philosopher %d is thinking\n", philo->id);
	if (sleep_ms(philo->data->t_sleep))
		return ((void *)EXIT_FAILURE);
	return ((void *)EXIT_SUCCESS);
}
