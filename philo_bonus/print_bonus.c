/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:23:00 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/30 09:23:00 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n >= 0 && n < 10)
		ft_putchar(n + '0');
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void	print_status(t_vars *vars, int id, char *state)
{
	int	now;

	now = get_time() - vars->start;
	sem_wait(vars->writing);
	ft_putnbr(now);
	write(1, " ", 1);
	ft_putnbr(id);
	write(1, " ", 1);
	write(1, state, ft_strlen(state));
	write(1, "\n", 1);
	if (state[0] != 'd')
		sem_post(vars->writing);
}

int	error_msg(int id)
{
	write(2, "Error", 5);
	if (id == -2)
		write(2, ":\tWrong number of arguments", 26);
	else if (id == -3)
		write(2, ":\tInvalid Arguments", 18);
	else if (id == -4)
		write(2, ":\tCannot allocate memory", 23);
	else if (id == -5)
		write(2, ":\tFailed to open semaphore", 25);
	else if (id == -6)
		write(2, ":\tFailed to create thread", 24);
	write(2, "\n", 1);
	return (0);
}
