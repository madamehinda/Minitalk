/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:08:16 by hferjani          #+#    #+#             */
/*   Updated: 2022/10/24 16:00:00 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_list
{
	char			character;
	struct s_list	*next;
}	t_list;

typedef struct g_struct
{
	t_list	*buffer;
	char	character;
	char	*string;
	int		current_bit;
	int		counter;
	int		sent;
	int		received;
	int		server_pid;
	int		client_pid;
}t_struct;

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	print(t_list *head);

#endif
