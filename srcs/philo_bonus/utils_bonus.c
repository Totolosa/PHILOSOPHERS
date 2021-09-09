/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:58:22 by tdayde            #+#    #+#             */
/*   Updated: 2021/09/09 20:54:24 by tdayde           ###   ########lyon.fr   */
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
	return (0);
}

void	free_all_bonus(t_main *main)
{
	int	i;

	i = 0;
	sem_close(main->fork_sem);
	if (main->tread_philo)
		free(main->tread_philo);
	if (main->eat_philo)
		free(main->eat_philo);
	if (main->fork_mut)
		free(main->fork_mut);
	if (main->philos_done)
		free(main->philos_done);
	if (main->end_main)
		free(main->end_main);
}
