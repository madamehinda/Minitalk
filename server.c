/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:07:28 by hferjani          #+#    #+#             */
/*   Updated: 2022/10/24 14:15:50 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "minitalk.h"

t_struct	g_list;

void	print_list(t_list *head)
{
	while (head != NULL)
	{
		ft_putchar_fd(head->character, 1);
		head = head->next;
	}
}

void	free_stack(t_list **stack)
{
	t_list	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

void	push(t_list**head_ref, char new_data)
{
	t_list	*new_node;
	t_list	*tmp;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->character = new_data;
	new_node->next = NULL;
	if (!*head_ref)
	(*head_ref) = new_node;
	else
	{
		tmp = (*head_ref);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	handler_server(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_list.client_pid = info->si_pid;
	if (sig == SIGUSR1)
	{
		g_list.character <<= 1;
		g_list.character |= 1;
	}
	else
		g_list.character <<= 1;
	g_list.current_bit++;
	if (g_list.current_bit == 8)
	{
		push(&g_list.buffer, g_list.character);
		if (!g_list.character)
		{
			print_list(g_list.buffer);
			ft_putchar_fd('\n', 1);
			free_stack(&g_list.buffer);
			g_list.buffer = NULL;
			kill(g_list.client_pid, SIGUSR1);
			usleep(100);
		}
		g_list.current_bit = 0;
	}
	kill(g_list.client_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_sigaction = handler_server;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
	{	
		pause();
	}
	return (0);
}
