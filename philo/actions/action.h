/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 12:50:45 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/28 13:53:06 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

# include <pthread.h>
# include <stdio.h>
# include "../struct.h"
# include "../utils/utils.h"

# define THINKING "is thinking\n"
# define TAKEN_FORK "has taken a fork\n"
# define EATING "is eating\n"
# define SLEEPING "is sleeping\n"
# define DIED "died\n"

void	*actions(void *arg);
void	*monitor1(void *arg);
void	*monitor2(void *arg);
void	print_action(t_philo *philo, const char *action);
int		is_finished(t_philo *philo);
void	sleep_and_think(t_philo *philo);
void	lock_print_left(t_philo *philo);

#endif
