/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:37:55 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/28 13:52:27 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	error(const char *msg)
{
	printf("%s", msg);
	return (EXIT_FAILURE);
}

int	error_time(const char *msg)
{
	printf("%s", msg);
	return (-1);
}
