/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:33:14 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/23 16:32:41 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (error(ERR_INVALID_ARGS));
	if (init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

