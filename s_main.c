/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 10:37:51 by pnuti             #+#    #+#             */
/*   Updated: 2021/08/29 21:26:19 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	terminate(int c_pid, u_int8_t *string, size_t *count, int term)
{
	usleep(100);
	write(1, string, count[1] + 1);
	if (term)
		ft_putchar_fd('\n', 1);
	ft_bzero(string, 10000);
	count[1] = 0;
	if (term)
	{
		if (kill(c_pid, SIGUSR2) == -1)
			throw_error();
	}
	else if (kill(c_pid, SIGUSR1) == -1)
		throw_error();
}

static void	handle_sig(int sig, siginfo_t *info, void *idle)
{
	static size_t	count[2];
	static u_int8_t	string[10000];

	(void)idle;
	if (count[1] == 9999)
		terminate(info->si_pid, string, count, 0);
	string[count[1]] = string[count[1]] << 1;
	if (sig == SIGUSR2)
		string[count[1]]++;
	count[0]++;
	if (count[0] == 8)
	{
		count[0] = 0;
		if (!string[count[1]])
			terminate(info->si_pid, string, count, 1);
		else
		{
			count[1]++;
			if (kill(info->si_pid, SIGUSR1) == -1)
				throw_error();
		}
	}
	else if (kill(info->si_pid, SIGUSR1) == -1)
		throw_error();
}

static void	define_sig(void)
{
	t_sigact	sa;

	sa.sa_sigaction = &handle_sig;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(2, "Error\n", 7);
		exit(-1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error\n", 7);
		exit(-1);
	}
}

int	main(void)
{
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	define_sig();
	while (1)
		usleep(1);
	return (0);
}
