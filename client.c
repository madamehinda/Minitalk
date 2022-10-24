/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:07:03 by hferjani          #+#    #+#             */
/*   Updated: 2022/10/24 15:58:29 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "minitalk.h"

t_struct	g_list;

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*s;

	s = (char *)str;
	i = 0;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

void	server_response(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_putnbr_fd(g_list.sent, 1);
		ft_putstr_fd(" signals sent and received\n", 1);
		ft_putstr_fd("message delivered\n", 1);
		exit(0);
	}
	else if (sig == SIGUSR2)
	{
		++g_list.sent;
	}
}

void	ft_binary(int pid, char *str)
{
	char	c;

	(void) pid;
	(void) str;
	c = *g_list.string++;
	g_list.counter = 8;
	while (--g_list.counter >= 0)
	{
		if (c & 1 << g_list.counter)
			kill(g_list.server_pid, SIGUSR1);
		else
			kill(g_list.server_pid, SIGUSR2);
		usleep(1000);
	}
}

void	send_message(int pid, char *str)
{
	(void) str;
	(void) pid;
	while (*g_list.string)
	{
		ft_binary(g_list.server_pid, g_list.string);
	}
	ft_binary(g_list.server_pid, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = server_response;
	if (argc != 3)
		return (1);
	g_list.server_pid = ft_atoi(argv[1]);
	g_list.string = argv[2];
	if (!ft_strlen(argv[2]) || g_list.server_pid < 0
		|| g_list.server_pid > 4194304)
		return (1);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	send_message(g_list.server_pid, g_list.string);
	while (1)
	{
		pause();
	}
}
