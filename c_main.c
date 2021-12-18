/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnuti <pnuti@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 09:38:16 by pnuti             #+#    #+#             */
/*   Updated: 2021/08/30 14:42:54 by pnuti            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_count[2];

static void	send_string(u_int8_t *string, int *i, int *j, int s_pid)
{
	if (*j < 0)
	{
		*j = 7;
		*i += 1;
	}
	if (!((string[*i] >> *j) % 2))
	{
		*j -= 1;
		if (kill(s_pid, SIGUSR1) == -1)
			throw_error();
	}
	else
	{
		*j -= 1;
		if (kill(s_pid, SIGUSR2) == -1)
			throw_error();
	}
}

static void	store_and_send(char *string, int pid)
{
	static char	to_send[10000];
	static int	i = 0;
	static int	j = 7;
	static int	s_pid;

	if (string)
		ft_strlcpy(to_send, string, 10000);
	if (pid)
		s_pid = pid;
	if (i == 9998 && j == -1)
	{
		g_count[1]++;
		i = 0;
		return ;
	}
	send_string((u_int8_t *)to_send, &i, &j, s_pid);
}

static void	handle_sig(int sig)
{
	usleep(10);
	if (sig == SIGUSR1)
		store_and_send(NULL, 0);
	else if (sig == SIGUSR2)
		exit(0);
}

static void	define_sig(void)
{
	t_sigact	sa;

	sa.sa_handler = &handle_sig;
	sa.sa_flags = SA_NODEFER;
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

int	main(int argc, char *argv[])
{
	int	s_pid;

	if (argc != 3 || !ft_atoi(argv[1]))
	{
		write(2, "Input not valid\n", 19);
		return (0);
	}
	define_sig();
	s_pid = ft_atoi(argv[1]);
	store_and_send(argv[argc - 1], s_pid);
	g_count[0]++;
	while (1)
	{
		if (g_count[0] == g_count[1])
		{
			store_and_send(argv[2] + (9998 * g_count[0]), 0);
			g_count[0]++;
		}
		usleep(1);
	}
	return (0);
}
