#include "Philosophers.h"



int	all_eat_count(t_vars *vars)
{
    int     i;
    int     count;
    t_philo *philo;

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

int check_starving(t_vars *vars)
{
    int     i;
    t_philo *philo;

    philo = vars->philo;
    while (vars->nb_eat == -2 || vars->nb_eat > all_eat_count(vars))
    {
        i = 0;
        while (i < vars->nb_philo)
        {
            if (philo[i].eating != 1 && (get_time() - philo[i].last_meal >= vars->die_time))
            {
                pthread_mutex_lock(&(vars->philo[i].eating));
				vars->death_time = 1;
                print_status(vars, i + 1, "died");
                return (0);
            }
            i++;
        }
    }
    return (0);
}

int start_simulation(t_vars *vars)
{
    int i;
    t_philo *philos;

    vars->start = get_time();
    init_philos(vars);
    if (pthread_mutex_init(&(vars->writing), NULL))
            return (-1);
    philos = vars->philo;
    vars->death_time = -1;
    i = 0;
    while (i < vars->nb_philo)
    {
		philos[i].last_meal = get_time();
        if (pthread_create(&(philos[i].th_id), NULL, &routine, philos + i) != 0)
            return (-1);
        i++;
		usleep(100);
    }
    check_starving(vars);
    return (0);
}

int error_msg(int id)
{
	//write(1, "Error\n", 6);
    return (0);
}

int main(int ac, char **av)
{
    t_vars  *vars;
    int     error;

    g_check = 0;
	vars = malloc(sizeof(t_vars));
    error = check_init_args(ac, av, vars);
    if (error != 1)
        return (error_msg(error));
	error = start_simulation(vars);
    if (error != 1)
        return (error_msg(error));
    return (0);
}
