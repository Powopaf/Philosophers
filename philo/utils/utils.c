/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:32:53 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/02 11:22:39 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <sys/time.h>
#include "../error/error.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_time(ERR_GETTIMEOFDAY));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	sleep_ms(int ms)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		remaining = ms - elapsed;
		if (remaining <= 0)
			break ;
		if (remaining > 1)
			usleep((remaining - 1) * 1000);
		else
			usleep(100);
	}
	return (EXIT_SUCCESS);
}
