/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:44:33 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/25 12:44:33 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	print_status(t_vars *vars, int id, char *state)
{
	int	now;

	now = get_time() - vars->start;
	pthread_mutex_lock(&(vars->writing));
	printf("%d %d %s\n", now, id, state);
	if (state[0] != 'd')
		pthread_mutex_unlock(&(vars->writing));
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
		write(2, ":\tFailed to create mutex", 23);
	else if (id == -6)
		write(2, ":\tFailed to create thread", 24);
	write(2, "\n", 1);
	return (0);
}
