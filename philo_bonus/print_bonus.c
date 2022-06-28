/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:44:33 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/25 12:44:33 by oessamdi         ###   ########.fr       */
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

void    ft_putnbr(int n)
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
