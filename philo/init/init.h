/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:07:15 by pifourni          #+#    #+#             */
/*   Updated: 2026/01/23 16:03:34 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "../philosophers.h"
# include "../error/error.h"
# include "../utils/utils.h"

int	init_data(t_data *data, int argc, char **argv);

#endif
