/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:47:40 by tdayde            #+#    #+#             */
/*   Updated: 2021/09/09 15:28:29 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_main *main)
{
	main->nbr_philo = ft_atoi_philo(argv[1]);
	if (main->nbr_philo < 1 || main->nbr_philo > INT_MAX)
		return (quit_prog("ERROR number of philosophers\n"));
	main->time_die = ft_atoi_philo(argv[2]);
	if (main->time_die < 1 || main->time_die > INT_MAX)
		return (quit_prog("ERROR time_to_die\n"));
	main->time_eat = ft_atoi_philo(argv[3]);
	if (main->time_eat < 1 || main->time_eat > INT_MAX)
		return (quit_prog("ERROR time_to_eat\n"));
	main->time_sleep = ft_atoi_philo(argv[4]);
	if (main->time_sleep < 1 || main->time_sleep > INT_MAX)
		return (quit_prog("ERROR time_to_sleep\n"));
	if (argc == 6)
	{
		main->eat_max = ft_atoi_philo(argv[5]);
		if (main->eat_max < 1 || main->eat_max > INT_MAX)
			return (quit_prog("ERROR number_of_times_philosopher_must_eat\n"));
	}
	return (0);
}

int	init(t_main *main)
{
	int	i;

	main->fork_mut = ft_calloc(main->nbr_philo, sizeof(pthread_mutex_t));
	if (!main->fork_mut)
		return (quit_prog("Malloc main->fork_mut error\n"));
	i = 0;
	while (i < main->nbr_philo)
		if (pthread_mutex_init(&main->fork_mut[i++], NULL))
			return (quit_prog("ERROR pthread_mutex_init\n"));
	if (pthread_mutex_init(&main->print_mut, NULL))
		return (quit_prog("ERROR pthread_mutex_init\n"));
	main->tread_philo = ft_calloc(main->nbr_philo, sizeof(pthread_t));
	if (!main->tread_philo)
		return (quit_prog("Malloc main->tread_philo error\n"));
	main->eat_philo = ft_calloc(main->nbr_philo, sizeof(t_eat_philo));
	if (!main->eat_philo)
		return (quit_prog("Malloc main->philos error\n"));
	main->philos_done = ft_calloc(main->nbr_philo, sizeof(int));
	if (!main->philos_done)
		return (quit_prog("Malloc main->philos_done error\n"));
	i = 0;
	if (!main->eat_max)
		while (i < main->nbr_philo)
			main->eat_philo[i++].n_eat = -1;
	return (0);
}

int	init_philo(int i, t_num_philo **philo, t_main *main)
{
	(*philo) = ft_calloc(1, sizeof(t_num_philo));
	if (!(*philo))
		return (quit_prog("Malloc philo error\n"));
	(*philo)->i = i;
	(*philo)->main = main;
	(*philo)->main->eat_philo[i].last_eat = main->start;
	pthread_mutex_init(&main->eat_philo[i].lock, NULL);
	return (0);
}
