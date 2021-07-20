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

float	get_time(struct timeval *stop, struct timeval *start)
{
	float	sec;
	float	mil;
	float	res;

	sec = ((float)stop->tv_sec - (float)start->tv_sec) * 1000;
	if (stop->tv_usec > start->tv_usec)
		mil = ((float)stop->tv_usec - (float)start->tv_usec) / 1000;
	else
		mil = ((float)stop->tv_usec + (1000000 - (float)start->tv_usec)) / 1000;
	res = sec + mil;
	// res = (((float)stop->tv_sec - (float)start->tv_sec) * 1000
	// 	+ ((float)stop->tv_usec - (float)start->tv_usec) / 1000);
	return (res);
}

void	philo_dead(t_philo *philo)
{
	struct timeval	tmp;
	
	// tmp = NULL;
	gettimeofday(&tmp, NULL);
	if ((int)((tmp.tv_usec - philo->last_eat->tv_usec) / 1000) > philo->main->time_die)
	{
		philo->main->dead = 1;
		// printf("%.2f : %d died\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
		printf("%.2f : %d died\n", get_time(&tmp, philo->main->start), philo->i);
	}
	// return (NULL);
}

int	philo_eat(t_philo *philo)
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
	printf("timelaps = %.2f\n", get_time(&tmp, philo->main->start));
	printf("\ntmp.tv_sec = %ld, tmp.tv_usec = %d, main->start->tv_sec = %ld, main->start->tv_usec = %d\n", tmp.tv_sec, tmp.tv_usec, philo->main->start->tv_sec, philo->main->start->tv_usec);
	// printf("%.2f : %d has taken a fork\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	printf("%.2f : %d has taken a fork\n", get_time(&tmp, philo->main->start), philo->i);
	gettimeofday(&tmp, NULL);
	// printf("%.2f : %d has taken a fork\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	printf("%.2f : %d has taken a fork\n", get_time(&tmp, philo->main->start), philo->i);
	pthread_mutex_lock(&philo->main->fork[philo->i]);
	// printf("%.2f : %d is eating\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	if (philo->last_eat)
	{
		free(philo->last_eat);
		philo->last_eat = NULL;
	}
	philo->last_eat = ft_calloc(1, sizeof(struct timeval));
	if (!philo->last_eat)
		return (quit_prog("Malloc philo->last_eat error\n"));
	gettimeofday(philo->last_eat, NULL);
	printf("%.2f : %d is eating\n", get_time(philo->last_eat, philo->main->start), philo->i);
	usleep(philo->main->time_eat * 1000);
	philo->n_eat++;
	if (philo->i == 0)
		pthread_mutex_unlock(&philo->main->fork[philo->main->nbr_philo - 1]);
	else
		pthread_mutex_unlock(&philo->main->fork[philo->i - 1]);
	pthread_mutex_unlock(&philo->main->fork[philo->i]);
	// printf("\nICI\n");
	gettimeofday(&tmp, NULL);
	// printf("%.2f : %d is sleeping\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	printf("%.2f : %d is sleeping\n", get_time(&tmp, philo->main->start), philo->i);
	usleep(philo->main->time_sleep * 1000);
	gettimeofday(&tmp, NULL);
	// printf("%.2f : %d is thinking\n", ((float)(tmp.tv_usec - philo->main->start->tv_usec) / 1000), philo->i);
	printf("%.2f : %d is thinking\n", get_time(&tmp, philo->main->start), philo->i);
	// usleep(philo->main->time_sleep * 1000);
	return (1);
}

void	*exec(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	printf("Philospher %d created\n", philo->i);
	while (!philo->main->dead
		|| (philo->main->eat_max && philo->n_eat < philo->main->eat_max))
	{
		philo_eat(philo);
		printf("fin philo_eat\n");
		// philo_dead(philo);
	}
	free(philo);
	return (NULL);
}

int	create_threads(t_main *main)
{
	int		i;
	t_philo	*philo;
	
	philo = NULL;
	main->philos = ft_calloc(main->nbr_philo, sizeof(pthread_t));
	if (!main->philos)
		return (quit_prog("Malloc main->philos error\n"));
	// gettimeofday(main->start, NULL);
	// printf("test\n");
	// printf("main->start->tv_usec = %ld\n",main->start->tv_usec);
	i = 0;
	while (i < main->nbr_philo)
	{
		philo = ft_calloc(1, sizeof(t_philo));
		if (!philo)
			return (quit_prog("Malloc philo error\n"));
		// printf("test\n");
		philo->i = i;
		philo->main = main;
		if (!main->start)
		{
			main->start = ft_calloc(1, sizeof(struct timeval));
			if (!main->start)
				return (quit_prog("Malloc main->start error\n"));
			gettimeofday(main->start, NULL);
			printf("main->start->tv_usec = %d\n",main->start->tv_usec);
		}
		if (pthread_create(&main->philos[i++], NULL, &exec, philo) != 0)
			return (quit_prog("ERROR pthread_create\n")); 
	}
	while (!main->dead)
		// || (philo->main->eat_max && philo->n_eat < philo->main->eat_max))
	{
		// philo_eat(philo);
		// printf("fin philo_eat\n");
		philo_dead(philo);
	}
	i = 0;
	while (i < main->nbr_philo)
	{
		if (pthread_join(main->philos[i++], NULL) != 0)
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