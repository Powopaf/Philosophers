/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:27:09 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/23 16:29:13 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <pthread.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				is_alive;
	struct s_data	*data;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

typedef struct s_data
{
	long 			start_time;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

#endif
