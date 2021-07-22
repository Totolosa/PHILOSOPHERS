#include "philo.h"

void	print_parsing(t_main *main)
{
	printf("PARSING :\n");
	printf("nbr_philo = %lld\n", main->nbr_philo);
	printf("time_die = %lld\n", main->time_die);
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

int	init_mutex(t_main *main)
{
	int	i;
	
	main->fork = ft_calloc(main->nbr_philo, sizeof(pthread_mutex_t));
	if (!main->fork)
		return (quit_prog("Malloc main->fork error\n"));
	i = 0;
	while (i < main->nbr_philo)
	{
		if (pthread_mutex_init(&main->fork[i++], NULL))
			return (quit_prog("ERROR pthread_mutex_init\n"));
	}
	return (0);
}

int	time_diff(struct timeval *stop, struct timeval *start, t_main *main)
{
	long	sec;
	int		mil;
	long	res;

	(void)main;
	// printf("\nget_time : stop.tv_sec = %ld, stop.tv_usec = %d, start->tv_sec = %ld, start->tv_usec = %d\n", stop->tv_sec, stop->tv_usec, start->tv_sec, start->tv_usec);
	// if (start == NULL)
	// 	start = main->start;
	// sec = (stop->tv_sec - start->tv_sec) * 1000;
	sec = (stop->tv_sec - start->tv_sec);
	// printf("sec = %ld\n", sec);
	if (sec != 0)
		sec *= 1000;
	// if (stop->tv_usec > start->tv_usec)
	mil = (stop->tv_usec - start->tv_usec) / 1000;
	// if (stop->tv_usec > start->tv_usec)
	// 	mil = ((long)stop->tv_usec - (long)start->tv_usec) / 1000;
	// else
	// 	mil = ((long)stop->tv_usec + (1000000 - (long)start->tv_usec)) / 1000;
	res = sec + mil;
	// res = (((long)stop->tv_sec - (long)start->tv_sec) * 1000
	// 	+ ((long)stop->tv_usec - (long)start->tv_usec) / 1000);
	if (main == NULL && res == 1000)
		printf("time_diff : sec = %ld, mil = %d, res = %ld, stop->tv_sec - start->tv_sec = %ld\nstop->tv_sec = %ld, start->tv_sec = %ld, stop->tv_usec = %d, start->tv_usec = %d\n", sec, mil, res, stop->tv_sec - start->tv_sec, stop->tv_sec, start->tv_sec, stop->tv_usec, start->tv_usec);
	return (res);
}

int	philo_eat(t_num_philo *philo)
{
	struct timeval	tmp;
	
	// tmp = NULL;
	if (philo->i == 0)
		pthread_mutex_lock(&philo->main->fork[philo->main->nbr_philo - 1]);
	else
		pthread_mutex_lock(&philo->main->fork[philo->i - 1]);
	// if (!philo->main->start->tv_usec)
	// 	gettimeofday(philo->main->start, NULL);
	gettimeofday(&tmp, NULL);
	// printf("timelaps = %.2d\n", time_diff(&tmp, philo->main->start));
	// printf("\ntmp.tv_sec = %ld, tmp.tv_usec = %d, main->start->tv_sec = %ld, main->start->tv_usec = %d\n", tmp.tv_sec, tmp.tv_usec, philo->main->start->tv_sec, philo->main->start->tv_usec);
	// printf("%.2f : %d has taken a fork\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	printf("%.2d : %d has taken a fork\n", time_diff(&tmp, philo->main->start, philo->main), philo->i);
	gettimeofday(&tmp, NULL);
	// printf("%.2d : %d has taken a fork\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	pthread_mutex_lock(&philo->main->fork[philo->i]);
	printf("%.2d : %d has taken a fork\n", time_diff(&tmp, philo->main->start, philo->main), philo->i);

	// if (philo->main->eat_philo[philo->i].last_eat)
	// {
	// 	free(philo->main->eat_philo[philo->i].last_eat);
	// 	philo->main->eat_philo[philo->i].last_eat = NULL;
	// }
	// philo->main->eat_philo[philo->i].last_eat = ft_calloc(1, sizeof(struct timeval));
	// if (!philo->main->eat_philo[philo->i].last_eat)
	// 	return (quit_prog("Malloc philo->main->eat_philo[philo->i].last_eat error\n"));
	gettimeofday(&philo->main->eat_philo[philo->i].last_eat, NULL);
	printf("%.2d : %d is eating\n", time_diff(&philo->main->eat_philo[philo->i].last_eat, philo->main->start, philo->main), philo->i);
	usleep(philo->main->time_eat * 1000);
	if (philo->main->eat_max)
		philo->main->eat_philo[philo->i].n_eat++;

	if (philo->i == 0)
		pthread_mutex_unlock(&philo->main->fork[philo->main->nbr_philo - 1]);
	else
		pthread_mutex_unlock(&philo->main->fork[philo->i - 1]);
	pthread_mutex_unlock(&philo->main->fork[philo->i]);
	// printf("\nICI\n");
	gettimeofday(&tmp, NULL);
	// printf("%.2d : %d is sleeping\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	printf("%.2d : %d is sleeping\n", time_diff(&tmp, philo->main->start, philo->main), philo->i);
	usleep(philo->main->time_sleep * 1000);
	gettimeofday(&tmp, NULL);
	// printf("%.2d : %d is thinking\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	printf("%.2d : %d is thinking\n", time_diff(&tmp, philo->main->start, philo->main), philo->i);
	// usleep(philo->main->time_sleep * 1000);
	return (1);
}

void	is_philo_dead(int i, t_main *main)
{
	struct timeval	tmp;
	long			diff;
	
	// tmp = NULL;
	gettimeofday(&tmp, NULL);
	// if ((int)((tmp.tv_usec - philo->last_eat->tv_usec) / 1000) > philo->main->time_die)
	// printf("i = %d\n", i);
	diff = time_diff(&tmp, &main->eat_philo[i].last_eat, NULL);
	if ((long long)diff > main->time_die)
	{
		printf("He died because he stayed %ld ms without eat\n", diff);
		main->dead = 1;
		printf("%.2d : %d died\n", time_diff(&tmp, main->start, main), i);
		// diff += 100000;
	}
	// return (NULL);
}

void	*exec(void *arg)
{
	t_num_philo	*philo;
	
	philo = (t_num_philo *)arg;
	printf("Philospher %d created\n", philo->i);
	while (!philo->main->dead
		|| (philo->main->eat_max
		&& philo->main->eat_philo[philo->i].n_eat < philo->main->eat_max))
	{
		philo_eat(philo);
		// printf("fin philo_eat\n");
		// philo_dead(philo);
	}
	free(philo);
	return (NULL);
}

int	create_threads(t_main *main)
{
	int			i;
	t_num_philo	*n_philo;
	
	// philo = NULL;
	main->tread_philo = ft_calloc(main->nbr_philo, sizeof(pthread_t));
	if (!main->tread_philo)
		return (quit_prog("Malloc main->tread_philo error\n"));
	main->eat_philo = ft_calloc(main->nbr_philo, sizeof(t_eat_philo));
	if (!main->eat_philo)
		return (quit_prog("Malloc main->philos error\n"));
	// gettimeofday(&main.start, NULL);
	// gettimeofday(main->start, NULL);
	// printf("test\n");
	// printf("main->start->tv_usec = %ld\n",main->start->tv_usec);
	i = 0;
	while (i < main->nbr_philo)
	{
		n_philo = ft_calloc(1, sizeof(t_num_philo));
		if (!n_philo)
			return (quit_prog("Malloc philo error\n"));
		n_philo->i = i;
		n_philo->main = main;
		if (!main->start)
		{
			main->start = ft_calloc(1, sizeof(struct timeval));
			if (!main->start)
				return (quit_prog("Malloc main->start error\n"));
			gettimeofday(main->start, NULL);
			printf("main->start->tv_usec = %d\n",main->start->tv_usec);
		}
		if (pthread_create(&main->tread_philo[i++], NULL, &exec, n_philo) != 0)
			return (quit_prog("ERROR pthread_create\n"));
		usleep(1000);
	}
	while (!main->dead)
		// || (philo->main->eat_max && philo->n_eat < philo->main->eat_max))
	{
		// philo_eat(philo);
		// printf("fin philo_eat\n");
		i = 0;
		while (i < main->nbr_philo)
			is_philo_dead(i++, main);
	}
	i = 0;
	while (i < main->nbr_philo)
	{
		if (pthread_join(main->tread_philo[i++], NULL) != 0)
			return (quit_prog("ERROR pthread_join\n"));
	}
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
	else if (init_mutex(&main))
		main.code_out = 1;
	else if (create_threads(&main))
		main.code_out = 1;
	free_all(&main);
	return (main.code_out);
}