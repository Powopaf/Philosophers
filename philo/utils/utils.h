/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:33:04 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/23 17:03:49 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stddef.h>
# include <sys/time.h>
# include "../error/error.h"

int	ft_atoi(const char *nptr);
int	sleep_ms(int ms);
long get_time();

#endif
