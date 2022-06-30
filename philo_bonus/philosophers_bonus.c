/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:22:49 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/30 09:22:49 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*check_starving(void *data)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *) data;
	vars = philo->vars;
	while (1)
	{
		if (get_time() - philo->last_meal >= vars->die_time)
		{
			sem_wait(philo->eat);
			print_status(vars, philo->id, "died");
			exit(1);
		}
	}
	return (NULL);
}

void	kill_child_processes(t_vars *vars)
{
	int	x;
	int	status;

	status = 0;
	while (!status)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
	}
	x = 0;
	while (x < vars->nb_philo)
	{
		kill(vars->philo[x].pid, SIGKILL);
		x++;
	}
}

int	start_simulation(t_vars *vars)
{
	int		i;
	t_philo	*philos;

	philos = vars->philo;
	vars->start = get_time();
	i = 0;
	while (i < vars->nb_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			philos[i].last_meal = get_time();
			if (pthread_create(&(philos[i].th_id),
					NULL, &check_starving, philos + i) != 0)
				return (-6);
			routine(philos + i);
			exit(1);
		}
		i++;
		usleep(100);
	}
	kill_child_processes(vars);
	return (1);
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	int		error;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (error_msg(-1));
	error = check_init_args(ac, av, vars);
	if (error != 1)
		return (error_msg(error));
	if (vars->nb_eat == 0)
		return (0);
	error = init_philos(vars);
	if (error != 1)
		return (error_msg(error));
	error = start_simulation(vars);
	if (error != 1)
		return (error_msg(error));
	return (0);
}
