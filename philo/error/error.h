/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:37:39 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/23 14:37:42 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <stdlib.h>

# define ERR_INVALID_ARGS "Error: Invalid arguments\n"
# define ERR_MALLOC_PHILO "Error: Memory alloc philo failed\n"
# define ERR_MALLOC_FORKS "Error: Memory alloc forks failed\n"

int	error(const char *msg);

#endif
