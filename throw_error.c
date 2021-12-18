/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 14:21:47 by pnuti             #+#    #+#             */
/*   Updated: 2021/08/28 14:25:31 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	throw_error(void)
{
	write(2, "Fatal! The signal could not be delivered!\n", 43);
	exit(-1);
}
