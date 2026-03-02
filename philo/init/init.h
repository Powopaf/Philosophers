/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:07:15 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 11:15:55 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <pthread.h>
# include "../struct.h"

int		init_data(t_data *data, int argc, char **argv, pthread_t **threads);
int		init_philo(t_data *data, pthread_t *threads);
int		cleanup(t_data *data, pthread_t *threads);
void	clean_mutexes(t_data *data, int j);
void	clean_forks(t_data *data, int j);

#endif
