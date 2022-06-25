#include "Philosophers.h"

void	print_status(t_vars *vars, int id, char *state)
{
	int	now;

	now = get_time() - vars->start;
	sem_wait(&(vars->writing));
    printf("%d %d %s\n", now, id, state);
	if (state[0] != 'd')
		sem_post(&(vars->writing));
}
