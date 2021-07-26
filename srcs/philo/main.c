#include "philo.h"

static void	is_philo_dead_or_sated(t_main *main)
{
	int	i;
	int	philo_sated;

	philo_sated = 0;
	i = -1;
	while (!main->dead && philo_sated < main->nbr_philo)
	{
		if (!main->philos_done[++i])
		{
			pthread_mutex_lock(&main->eat_philo[i].lock);
			if (time_diff(&main->eat_philo[i].last_eat) > main->time_die)
			{
				main->dead = 1;
				print_str_mutex("died", i, main);
			}
			pthread_mutex_unlock(&main->eat_philo[i].lock);
			if (main->eat_philo[i].done)
			{
				main->philos_done[i] = 1;
				philo_sated++;
			}
		}
		if (i == main->nbr_philo)
			i = -1;
	}
}

int	create_threads(t_main *main)
{
	int			i;
	t_num_philo	*philo;

	i = 0;
	philo = NULL;
	gettimeofday(&main->start, NULL);
	while (i < main->nbr_philo)
	{
		if (init_philo(i, &philo, main))
			return (1);
		if (pthread_create(&main->tread_philo[i++], NULL,
				&philosopher_life, philo) != 0)
			return (quit_prog("ERROR pthread_create\n"));
		usleep(50);
	}
	is_philo_dead_or_sated(main);
	i = 0;
	while (i < main->nbr_philo)
		if (pthread_join(main->tread_philo[i++], NULL) != 0)
			return (quit_prog("ERROR pthread_join\n"));
	if (!main->dead && main->eat_max)
		printf("ALL PHILOSOPHERS ARE SATED!\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (argc != 5 && argc != 6)
		return (quit_prog("ERROR number of arguments\n"));
	ft_bzero(&main, sizeof(t_main));
	if (check_args(argc, argv, &main))
		main.code_out = 1;
	else if (init(&main))
		main.code_out = 1;
	else if (create_threads(&main))
		main.code_out = 1;
	free_all(&main);
	return (main.code_out);
}
