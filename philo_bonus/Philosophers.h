/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:44:33 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/25 12:44:33 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

struct s_vars;

typedef struct	s_philo
{
	int				id;
	int				pid; 
	int				eating; 
	int				sleeping;   
	int				thinking;
	long long		last_meal;
	int				eat_count;
	pthread_t		th_id;
	sem_t			*eat;
	struct s_vars	*vars;
}				t_philo;

typedef struct	s_vars
{
	int				nb_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nb_eat;
	long long		start;
	sem_t			*philo_eating;
	sem_t			*forks;
	sem_t			*writing;
	t_philo			*philo;
	pthread_t		tid;
	pthread_t		eat_count;
}				t_vars;

void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
long long	get_time(void);
void		print_status(t_vars *vars, int id, char *state);
int			ft_atoi(char const *str);
int			check_args(int ac, char **av);
void		eat_routine(t_philo *philo);
void		*routine(void *data);
int			check_init_args(int ac, char **av, t_vars *v);
int			init_philos(t_vars *vars);
int			all_eat_count(t_vars *vars);
int			check_starving(t_philo *philo);
int			start_simulation(t_vars *vars);
int			error_msg(int id);

#endif
