/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:47:43 by tdayde            #+#    #+#             */
/*   Updated: 2021/09/09 20:52:19 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_diff(struct timeval *start)
{
	long			res;
	struct timeval	now;

	gettimeofday(&now, NULL);
	res = (now.tv_sec - start->tv_sec) * 1000
		+ (now.tv_usec - start->tv_usec) / 1000;
	return (res);
}

void	print_str_mutex(char *str, int i, t_main *main)
{
	pthread_mutex_lock(&main->print_mut);
	printf("%d : %d %s\n", time_diff(&main->start), i, str);
	pthread_mutex_unlock(&main->print_mut);
}

void	free_all(t_main *main)
{
	int	i;

	pthread_mutex_destroy(&main->print_mut);
	i = 0;
	if (main->fork_mut)
		while (i < main->nbr_philo)
			pthread_mutex_destroy(&main->fork_mut[i++]);
	i = 0;
	if (main->eat_philo)
		while (i < main->nbr_philo)
			pthread_mutex_destroy(&main->eat_philo[i++].lock);
	if (main->tread_philo)
		free(main->tread_philo);
	if (main->eat_philo)
		free(main->eat_philo);
	if (main->fork_mut)
		free(main->fork_mut);
	if (main->philos_done)
		free(main->philos_done);
}
