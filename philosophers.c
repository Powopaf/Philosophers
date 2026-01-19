/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:33:14 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/19 10:56:03 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *nptr);

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philosophers nb_philo t_die t_eat t_sleep nb_eat");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int	res;

	res = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res);
}
