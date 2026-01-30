/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:32:53 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/28 13:51:22 by pifourni         ###   ########.fr       */
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

	start = get_time();
	while (get_time() - start < ms)
		usleep(ms / 10);
	return (EXIT_SUCCESS);
}
