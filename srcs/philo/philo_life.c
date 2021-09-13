/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:47:22 by tdayde            #+#    #+#             */
/*   Updated: 2021/09/13 11:34:20 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_num_philo *phil)
{
	pthread_mutex_lock(&phil->main->eat_philo[phil->i].lock);
	gettimeofday(&phil->main->eat_philo[phil->i].last_eat, NULL);
	printf("%d : %d is eating\n", time_diff(&phil->main->start), phil->i);
	pthread_mutex_unlock(&phil->main->eat_philo[phil->i].lock);
	while (time_diff(&phil->main->eat_philo[phil->i].last_eat)
		< phil->main->time_eat)
		usleep(10);
	if (phil->main->eat_max)
	{
		phil->main->eat_philo[phil->i].n_eat++;
		if (phil->main->eat_philo[phil->i].n_eat == phil->main->eat_max)
			phil->main->eat_philo[phil->i].done = 1;
	}
}

static void	philo_sleep(t_num_philo *philo)
{
	struct timeval	start_thinking;

	gettimeofday(&start_thinking, NULL);
	pthread_mutex_lock(&philo->main->print_mut);
	printf("%d : %d is sleeping\n", time_diff(&philo->main->start), philo->i);
	pthread_mutex_unlock(&philo->main->print_mut);
	while (time_diff(&start_thinking) < philo->main->time_sleep)
		usleep(10);
}

void	*philosopher_life(void *arg)
{
	t_num_philo	*phil;

	phil = (t_num_philo *)arg;
	while (!phil->main->dead && !phil->main->eat_philo[phil->i].done)
	{
		if (phil->i == 0)
			pthread_mutex_lock(&phil->main->fork_mut[phil->main->nbr_philo
				- 1]);
		else
			pthread_mutex_lock(&phil->main->fork_mut[phil->i - 1]);
		print_str_mutex("has taken a fork", phil->i, phil->main);
		pthread_mutex_lock(&phil->main->fork_mut[phil->i]);
		print_str_mutex("has taken a fork", phil->i, phil->main);
		philo_eat(phil);
		if (phil->i == 0)
			pthread_mutex_unlock(&phil->main->fork_mut[phil->main->nbr_philo
				- 1]);
		else
			pthread_mutex_unlock(&phil->main->fork_mut[phil->i - 1]);
		pthread_mutex_unlock(&phil->main->fork_mut[phil->i]);
		philo_sleep(phil);
		print_str_mutex("is thinking", phil->i, phil->main);
	}
	free(phil);
	return (NULL);
}
