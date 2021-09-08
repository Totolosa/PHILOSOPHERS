/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:51:13 by tdayde            #+#    #+#             */
/*   Updated: 2021/09/08 20:00:46 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_main *main)
{
	gettimeofday(&main->eat_philo[main->i].last_eat, NULL);
	printf("%d : %d is eating\n", time_diff(&main->start), main->i);
	while (time_diff(&main->eat_philo[main->i].last_eat) < main->time_eat)
		usleep(10);
	sem_post(main->fork_sem);
	sem_post(main->fork_sem);
	if (main->eat_max)
		main->eat_philo[main->i].n_eat++;
}

static void	philo_sleep(t_main *main)
{
	struct timeval	start_sleeping;

	gettimeofday(&start_sleeping, NULL);
	printf("%d : %d is sleeping\n", time_diff(&main->start), main->i);
	while (time_diff(&start_sleeping) < main->time_sleep)
		usleep(10);
}

void	*analyse_philo_proces(void *arg)
{
	t_main	*main;

	main = (t_main *)arg;
	while (!main->dead && !main->eat_philo[main->i].done)
	{
		if (time_diff(&main->eat_philo[main->i].last_eat) > main->time_die)
		{
			if (time_diff(&main->eat_philo[main->i].last_eat) > main->time_die)
			{
				print_str_sem("is dead", main->i, main);
				exit(1);
			}
		}
		else if (main->eat_philo[main->i].n_eat == main->eat_max)
		{
			print_str_sem("is done", main->i, main);
			exit(2);
		}
	}
	return (NULL);
}

void	philosopher_life_bonus(t_main *main)
{
	sem_wait(main->start_sem);
	if (main->i > main->nbr_philo / 2)
		usleep(10);
	gettimeofday(&main->start, NULL);
	while (42)
	{
		sem_wait(main->fork_sem);
		print_str_sem("has taken a fork", main->i, main);
		sem_wait(main->fork_sem);
		print_str_sem("has taken a fork", main->i, main);
		philo_eat(main);
		philo_sleep(main);
		print_str_sem("is thinking", main->i, main);
	}
}
