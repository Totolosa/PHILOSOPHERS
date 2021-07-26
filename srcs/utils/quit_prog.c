#include "philo.h"

int	quit_prog(char *str)
{
	if (str)
		ft_putstr_fd(str, 1);
	return (1);
}

void	free_all(t_main *main)
{
	int	i;

	pthread_mutex_destroy(&main->print_mut);
	i = 0;
	if (main->fork_mut)
		while (i < main->nbr_philo)
			pthread_mutex_destroy(&main->fork_mut[i++]);
	i = 0;
	if (main->eat_philo)
		while (i < main->nbr_philo)
			pthread_mutex_destroy(&main->eat_philo[i++].lock);
	if (main->tread_philo)
		free(main->tread_philo);
	if (main->eat_philo)
		free(main->eat_philo);
	if (main->fork_mut)
		free(main->fork_mut);
	if (main->philos_done)
		free(main->philos_done);
}

void	free_all_bonus(t_main *main)
{
	int	i;

	i = 0;
	sem_close(main->fork_sem);
	// pthread_mutex_destroy(&main->print_mut);
	// if (main->fork_mut)
	// 	while (i < main->nbr_philo)
	// 		pthread_mutex_destroy(&main->fork_mut[i++]);
	// i = 0;
	// if (main->eat_philo)
	// 	while (i < main->nbr_philo)
	// 		pthread_mutex_destroy(&main->eat_philo[i++].lock);
	if (main->tread_philo)
		free(main->tread_philo);
	if (main->eat_philo)
		free(main->eat_philo);
	if (main->fork_mut)
		free(main->fork_mut);
	if (main->philos_done)
		free(main->philos_done);
}
