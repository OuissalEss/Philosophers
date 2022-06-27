/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:44:33 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/25 12:44:33 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	all_eat_count(t_vars *vars)
{
	int		i;
	int		count;
	t_philo	*philo;

	philo = vars->philo;
	count = philo[0].eat_count;
	i = 1;
	while (i < vars->nb_philo)
	{
		if (philo[i].eat_count < count)
			count = philo[i].eat_count;
		i++;
	}
	return (count);
}

int	check_starving(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	while (1)
	{
		if (philo->eating != 1 && (get_time() - philo->last_meal >= vars->die_time))
		{
			sem_wait(philo->eat);
			print_status(vars, philo->id, "died");
			exit(1);
		}
	}
	return (0);
}

void	kill_child_processes(t_vars *vars)
{
	int	i;
	int	x;
	int	status;

	i = 0;
	while (i < vars->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) || WIFEXITED(status))
		{
			x = 0;
			while (x < vars->nb_philo)
			{
				kill(vars->philo[x].pid, SIGKILL);
				x++;
			}
		}
		i++;
	}
}

void	*check_eat(void *data)
{
	int		cp;
	int		i;
	t_vars	*vars;

	cp = 0;
	vars = (t_vars *)data;
	while (cp < vars->nb_eat)
	{
		i = 0;
		while (i < vars->nb_philo)
		{
			sem_wait(vars->philo_eating);
			i++;
		}
		cp++;
	}
	i = 0;
	while (i < vars->nb_philo)
	{
		kill(vars->philo[i].pid, SIGKILL);
		i++;
	}
	return (NULL);
}

int	start_simulation(t_vars *vars)
{
	int		i;
	t_philo	*philos;

	if (vars->nb_eat != -2)
		if (pthread_create(&(vars->eat_count), NULL, &check_eat, vars) != 0)
				return (-1);
	philos = vars->philo;
	vars->start = get_time();
	i = 0;
	while (i < vars->nb_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			philos[i].last_meal = get_time();
			if (pthread_create(&(philos[i].th_id), NULL, &routine, philos + i) != 0)
				return (-1);
			check_starving(philos + i);
			exit(1);
		}
		i++;
		usleep(100);
	}
	kill_child_processes(vars);
	return (0);
}

int	error_msg(int id)
{
	if (id == -1)
		write(2, "Error\n", 6);
	else if (id == -2)
		write(2, "Wrong number of arguments\n", 26);
	else if (id == -3)
		write(2, "Invalid Arguments\n", 18);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	int		error;

	vars = malloc(sizeof(t_vars));
	error = check_init_args(ac, av, vars);
	if (error != 1)
		return (error_msg(error));
	error = init_philos(vars);
	error = start_simulation(vars);
	if (error != 1)
		return (error_msg(error));
	return (0);
}
