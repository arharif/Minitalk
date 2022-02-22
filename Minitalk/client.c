/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arharif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:19:01 by arharif           #+#    #+#             */
/*   Updated: 2022/02/22 17:19:14 by arharif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	int	pid;
	int	i;

	if (ac != 3)
	{
		write(1, "Invalid Parameters.\n", 21);
	}
	else
	{
		pid = ft_atoi(av[1]);
		i = 0;
		while (av[2][i])
		{
			bits(pid, av[2][i]);
			i++;
		}
		bits(pid, av[2][i]);
	}
	return (0);
}
