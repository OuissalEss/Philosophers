/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:23:12 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/30 09:23:12 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	eat_routine(t_philo *philo)
{
	t_vars		*vars;

	vars = philo->vars;
	sem_wait(vars->forks);
	print_status(vars, philo->id, "has taken a fork");
	sem_wait(vars->forks);
	print_status(vars, philo->id, "has taken a fork");
	philo->last_meal = get_time();
	sem_wait(philo->eat);
	print_status(vars, philo->id, "is eating");
	usleep((vars->eat_time - 10) * 1000);
	while (get_time() - philo->last_meal < vars->eat_time)
		;
	sem_post(philo->eat);
	sem_post(philo->vars->philo_eating);
	sem_post(vars->forks);
	sem_post(vars->forks);
	philo->eat_count++;
	if (philo->eat_count == vars->nb_eat)
		exit (0);
}

void	*routine(t_philo *philo)
{
	long long	start_sleeping;
	t_vars		*vars;

	vars = philo->vars;
	while (1)
	{
		eat_routine(philo);
		print_status(vars, philo->id, "is sleeping");
		start_sleeping = get_time();
		usleep((vars->sleep_time - 10) * 1000);
		while (get_time() - start_sleeping < vars->sleep_time)
			;
		print_status(vars, philo->id, "is thinking");
	}
	return (0);
}
