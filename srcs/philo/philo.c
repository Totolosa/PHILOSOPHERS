#include "philo.h"

void	print_parsing(t_main *main)
{
	printf("PARSING :\n");
	printf("nbr_philo = %lld\n", main->nbr_philo);
	printf("time_die = %ld\n", main->time_die);
	printf("time_eat = %lld\n", main->time_eat);
	printf("time_sleep = %lld\n", main->time_sleep);
	printf("eat_max = %lld\n", main->eat_max);
}

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
	print_parsing(main);
	return (0);
}

int	init(t_main *main)
{
	int	i;
	
	main->fork = ft_calloc(main->nbr_philo, sizeof(pthread_mutex_t));
	if (!main->fork)
		return (quit_prog("Malloc main->fork error\n"));
	i = 0;
	while (i < main->nbr_philo)
		if (pthread_mutex_init(&main->fork[i++], NULL))
			return (quit_prog("ERROR pthread_mutex_init\n"));
	if (pthread_mutex_init(&main->print, NULL))
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

int	time_diff(struct timeval *start)
{
	// long			sec;
	// int				mil;
	long			res;
	struct timeval	now;

	gettimeofday(&now, NULL);
	// sec = (now.tv_sec - start->tv_sec) * 1000;
	// mil = (now.tv_usec - start->tv_usec) / 1000;
	// res = sec + mil;
	// if (res == 1000)
	// 	printf("time_diff : sec = %ld, mil = %d, res = %ld, now->tv_sec - start->tv_sec = %ld\nnow->tv_sec = %ld, start->tv_sec = %ld, now->tv_usec = %d, start->tv_usec = %d\n", sec, mil, res, now.tv_sec - start->tv_sec, now.tv_sec, start->tv_sec, now.tv_usec, start->tv_usec);
	res = (now.tv_sec - start->tv_sec) * 1000 + (now.tv_usec - start->tv_usec) / 1000;
	return (res);
}

void	manual_usleep(int time)
{
	// int	tmp;
	// int	to_sleep;
	
	// tmp = 0;
	// to_sleep = time * 1000;
	// while (tmp < to_sleep)
	// {
	// 	usleep(10);
	// 	tmp += 10;
	// }
	usleep(time * 1000);
}

void	print_str_mutex(char *str, int i, t_main *main)
{
	pthread_mutex_lock(&main->print);
	printf("%d : %d %s\n", time_diff(&main->start), i, str);
	pthread_mutex_unlock(&main->print);
}

void	philo_eat_mutex(t_num_philo *philo)
{
	pthread_mutex_lock(&philo->main->eat_philo[philo->i].lock);
	gettimeofday(&philo->main->eat_philo[philo->i].last_eat, NULL);
	printf("%d : %d is eating\n", time_diff(&philo->main->start), philo->i);
	pthread_mutex_unlock(&philo->main->eat_philo[philo->i].lock);
	manual_usleep(philo->main->time_eat);
	if (philo->main->eat_max)
	{
		philo->main->eat_philo[philo->i].n_eat++;
		if (philo->main->eat_philo[philo->i].n_eat == philo->main->eat_max)
			philo->main->eat_philo[philo->i].done = 1;
	}
}

void	is_philo_dead_or_sated(t_main *main)
{
	int	i;
	int philo_sated;
	
	philo_sated = 0;
	i = 0;
	while (!main->dead && philo_sated < main->nbr_philo)
	{
		if (!main->philos_done[i])
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
				print_str_mutex("is done", i, main);
			}
		}
		i++;
		if (i == main->nbr_philo)
			i = 0;
	}
}

void	*philosopher_life(void *arg)
{
	t_num_philo	*philo;
	
	philo = (t_num_philo *)arg;
	while (!philo->main->dead && !philo->main->eat_philo[philo->i].done)
	{
		if (philo->i == 0)
			pthread_mutex_lock(&philo->main->fork[philo->main->nbr_philo - 1]);
		else
			pthread_mutex_lock(&philo->main->fork[philo->i - 1]);
		print_str_mutex("has taken a fork", philo->i, philo->main);
		pthread_mutex_lock(&philo->main->fork[philo->i]);
		print_str_mutex("has taken a fork", philo->i, philo->main);
		philo_eat_mutex(philo);
		if (philo->i == 0)
			pthread_mutex_unlock(&philo->main->fork[philo->main->nbr_philo - 1]);
		else
			pthread_mutex_unlock(&philo->main->fork[philo->i - 1]);
		pthread_mutex_unlock(&philo->main->fork[philo->i]);
		print_str_mutex("is sleeping", philo->i, philo->main);
		manual_usleep(philo->main->time_sleep);
		print_str_mutex("is thinking", philo->i, philo->main);
	}
	free(philo);
	return (NULL);
}

int	create_threads(t_main *main)
{
	int			i;
	t_num_philo	*n_philo;
	
	i = 0;
	gettimeofday(&main->start, NULL);
	while (i < main->nbr_philo)
	{
		n_philo = ft_calloc(1, sizeof(t_num_philo));
		if (!n_philo)
			return (quit_prog("Malloc philo error\n"));
		n_philo->i = i;
		n_philo->main = main;
		pthread_mutex_init(&main->eat_philo[i].lock, NULL);
		if (pthread_create(&main->tread_philo[i++], NULL, &philosopher_life, n_philo) != 0)
			return (quit_prog("ERROR pthread_create\n"));
		usleep(200);
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