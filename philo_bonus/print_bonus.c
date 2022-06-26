/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:44:33 by oessamdi          #+#    #+#             */
/*   Updated: 2022/06/25 12:44:33 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	print_status(t_vars *vars, int id, char *state)
{
	int	now;  

	now = get_time() - vars->start;
	sem_wait(vars->writing);
	printf("%d %d %s\n", now, id, state);
	if (state[0] != 'd')
		sem_post(vars->writing);
}
