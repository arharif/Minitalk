/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arharif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:17:15 by arharif           #+#    #+#             */
/*   Updated: 2022/02/22 17:17:32 by arharif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int sig, siginfo_t *sig_info, void *b)
{
	(void)sig_info;
	(void)b;
	if (sig == SIGUSR1)
	{
		write(1, "The Signal Is Received\n", 24);
	}
}

void	bits(int pid, char c)
{
	unsigned int	one;
	unsigned int	and;
	unsigned int	j;

	j = 0;
	one = 0b10000000;
	while (j < 8)
	{
		and = c & one;
		if (and == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep (800);
		c = c << 1;
		j++;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	int					i;
	struct sigaction	sig_struct;

	if (ac != 3)
	{
		write(1, "Invalid Parameters.\n", 21);
	}
	else
	{
		sig_struct.__sigaction_u.__sa_sigaction = &sig_handler;
		sig_struct.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sig_struct, NULL);
		pid = ft_atoi(av[1]);
		i = 0;
		while (av[2][i])
		{
			bits(pid, av[2][i]);
			i++;
		}
		bits(pid, av[2][i]);
	}
}
