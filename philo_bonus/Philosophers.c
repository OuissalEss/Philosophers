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
			return (0);
		}
	}
	return (0);
}

void	kill_child_processes(t_vars *vars)
{
	int	i;
	int	x;
	int	status;

	while (i < vars->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) || WIFEXITED(status))
		{
			while (x < vars->nb_philo)
			{
				kill(vars->philo[x].pid, SIGKILL);
				x++;
			}
		}
		i++;
	}
}

void	check_eat(t_vars *vars)
{
	int	cp;
	int	i;

	cp = 0;
	while (cp < vars->nb_eat)
	{
		while (i < vars->nb_philo)
		{
			wait(vars->philo_eating);
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
}

int	start_simulation(t_vars *vars)
{
	int		i;
	t_philo	*philos;

	if (vars->eat_time != -2)
		if (pthread_create(&(vars->eat_count), NULL, &check_eat, philos + i) != 0)
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
	//write(1, "Error\n", 6);
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
