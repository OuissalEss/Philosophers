#include "Philosophers.h"

int ft_atoi(char const *str)
{
    unsigned long   res;
    int             sign;
    int             i;

    res = 0;
    i = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = (res * 10) + str[i] - '0';
        i++;
    }
    if (str[i] || res > 9223372036854775807)
        return (-1);
    return ((int) res);
}

int check_init_args(int ac, char **av, t_vars *v)
{
    if (ac < 5 || ac > 6)
        return (-1);
    v->nb_philo = ft_atoi(av[1]);
    v->die_time = ft_atoi(av[2]);
    v->eat_time = ft_atoi(av[3]);
    v->sleep_time = ft_atoi(av[4]);
    v->nb_eat = -2;
    if (ac == 6)
        v->nb_eat = ft_atoi(av[5]);
    if (v->nb_philo < 1 || v->die_time < 0 || v->eat_time < 0 || v->sleep_time < 0 || v->nb_eat == -1)
        return (-1);
    return (1);
}

int init_philos(t_vars *vars)
{
    int i;
    t_philo *philo;

    i = 0;
    philo = malloc(sizeof(t_philo) * vars->nb_philo);
    while (i < vars->nb_philo)
    {
        philo[i].id = i + 1;
        philo[i].eating = 0;
        philo[i].sleeping = 0;
        philo[i].thinking = 0;
        philo[i].eat_count = 0;
        if (pthread_mutex_init(&(philo[i].right_fork), NULL))
            return (-1);
		philo[i].vars = vars;
        i++;
    }
	vars->philo = philo;
    return (0);
}