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
	{
		main->eat_philo[main->i].n_eat++;
		if (main->eat_philo[main->i].n_eat == main->eat_max)
			main->eat_philo[main->i].done = 1;
	}
}

static void	philo_sleep(t_main *main)
{
	struct timeval	start_thinking;

	gettimeofday(&start_thinking, NULL);
	printf("%d : %d is sleeping\n", time_diff(&main->start), main->i);
	while (time_diff(&start_thinking) < main->time_sleep)
		usleep(10);
}

void	*analyse_philo_proces(void *arg)
{
	t_main	*main;
	int	i;
	int	philo_sated;

	main = (t_main *)arg;
	philo_sated = 0;
	i = -1;
	while (!main->dead && !main->eat_philo[++i].done)
	{
		if (time_diff(&main->eat_philo[i].last_eat) > main->time_die)
		{
			print_str_sem("died", i, main);
			exit(1);
		}
		else if (main->eat_philo[main->i].done)
		{
			print_str_sem("is done", i, main);
			exit(2);
		}
		if (i == main->nbr_philo - 1)
			i = -1;
	}
	return (NULL);
}

void	philosopher_life_bonus(t_main *main)
{
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
	// free(phil);
	// return (NULL);
}
