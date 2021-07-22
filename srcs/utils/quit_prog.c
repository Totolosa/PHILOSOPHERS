#include "philo.h"

int	quit_prog(char *str)
{
	if (str)
		ft_putstr_fd(str, 1);
	return (1);
}

void	free_all(t_main *main)
{
	int i;
	
	i = 0;
	if (main->fork)
		while (i < main->nbr_philo)
			pthread_mutex_destroy(&main->fork[i++]);
	if (main->tread_philo)
		free(main->tread_philo);
	if (main->eat_philo)
		free(main->eat_philo);
	if (main->fork)
		free(main->fork);
	if (main->start)
		free(main->start);
}