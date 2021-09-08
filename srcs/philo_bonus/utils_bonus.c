/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:58:22 by tdayde            #+#    #+#             */
/*   Updated: 2021/09/08 19:58:35 by tdayde           ###   ########lyon.fr   */
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

void	print_str_sem(char *str, int i, t_main *main)
{
	sem_wait(main->print_sem);
	printf("%d : %d %s\n", time_diff(&main->start), i, str);
	sem_post(main->print_sem);
}

int	init_philo(int i, t_num_philo **philo, t_main *main)
{
	(*philo) = ft_calloc(1, sizeof(t_num_philo));
	if (!(*philo))
		return (quit_prog("Malloc philo error\n"));
	(*philo)->i = i;
	(*philo)->main = main;
	pthread_mutex_init(&main->eat_philo[i].lock, NULL);
	return (0);
}
