/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:37:39 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/28 13:52:04 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <stdlib.h>

# define ERR_INVALID_ARGS "Error: Invalid arguments\n"
# define ERR_MALLOC_PHILO "Error: Memory alloc philo failed\n"
# define ERR_MALLOC_FORKS "Error: Memory alloc forks failed\n"
# define ERR_GETTIMEOFDAY "Error: Can't get time of day\n"
# define ERR_MUTEX_INIT "Error: Mutex initialization failed\n"
# define ERR_THREAD_CREATE "Error: Thread creation failed\n"
# define ERR_THREAD_JOIN "Error: Thread join failed\n"
# define ERR_MALLOC_THREADS "Error: Memory alloc threads failed\n"
# define ERR_THREAD_DETACH "Error: Thread detach failed\n"	

int	error(const char *msg);
int	error_time(const char *msg);

#endif
