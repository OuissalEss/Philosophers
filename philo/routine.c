/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:44:49 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/25 12:44:49 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_left_philo_id(t_philo *philo)
{
	t_vars		*vars;

	vars = philo->vars;
	if (vars->nb_philo == 1)
		return (philo->id - 1);
	else if (philo->id == 1)
		return (vars->nb_philo - 1);
	else
		return (philo->id - 2);
}

void	eat_routine(t_philo *philo)
{
	long long	start_eating;
	int			left_philo_id;
	t_vars		*vars;

	vars = philo->vars;
	left_philo_id = get_left_philo_id(philo);
	pthread_mutex_lock(&(vars->philo[left_philo_id].right_fork));
	print_status(vars, philo->id, "has taken a fork");
	pthread_mutex_lock(&(vars->philo[philo->id - 1].right_fork));
	print_status(vars, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->eat));
	philo->eating = 1;
	start_eating = get_time();
	philo->last_meal = start_eating;
	print_status(vars, philo->id, "is eating");
	usleep((vars->eat_time - 10) * 1000);
	while (get_time() - start_eating < vars->eat_time)
		;
	philo->eat_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&(philo->eat));
	pthread_mutex_unlock(&(vars->philo[philo->id - 1].right_fork));
	pthread_mutex_unlock(&(vars->philo[left_philo_id].right_fork));
}

void	*routine(void *data)
{
	long long	start_sleeping;
	t_philo		*philo;
	t_vars		*vars;

	philo = (t_philo *) data;
	vars = philo->vars;
	while (vars->death_time == -1)
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
