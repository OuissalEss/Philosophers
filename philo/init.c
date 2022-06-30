/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:40:57 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/25 12:40:57 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_atoi(char const *str)
{
	unsigned long	res;
	int				i;

	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	if (str[i] || res > 2147483647)
		return (-1);
	return ((int) res);
}

int	check_init_args(int ac, char **av, t_vars *v)
{
	if (ac < 5 || ac > 6)
		return (-2);
	v->nb_philo = ft_atoi(av[1]);
	v->die_time = ft_atoi(av[2]);
	v->eat_time = ft_atoi(av[3]);
	v->sleep_time = ft_atoi(av[4]);
	v->nb_eat = -2;
	if (ac == 6)
		v->nb_eat = ft_atoi(av[5]);
	if (v->nb_philo < 1 || v->die_time < 0 || v->eat_time < 0
		|| v->sleep_time < 0 || v->nb_eat == -1)
		return (-3);
	return (1);
}

int	init_philos(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * vars->nb_philo);
	if (!philo)
		return (-4);
	while (i < vars->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].sleeping = 0;
		philo[i].thinking = 0;
		philo[i].eat_count = 0;
		if (pthread_mutex_init(&(philo[i].right_fork), NULL))
			return (-5);
		if (pthread_mutex_init(&(philo[i].eat), NULL))
			return (-5);
		philo[i].vars = vars;
		i++;
	}
	vars->philo = philo;
	return (1);
}
