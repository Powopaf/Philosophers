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

int	check_death(t_philo *philo)
{
	if (get_time() - philo->data->start_time > philo->data->t_die)
		return (1);
	return (0);
}
