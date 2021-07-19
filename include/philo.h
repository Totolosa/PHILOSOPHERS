#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft.h"

typedef struct	s_main
{
	long long		nbr_philo;
	pthread_t		*philos;
	pthread_mutex_t	*fork;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	long long		eat_max;
	struct timeval	*start;
	// pthread_mutex_t	*fork;
	int				dead;
	int				*i;
	int				code_out;
}				t_main;

typedef struct	s_philo
{
	int				i;
	int				n_eat;
	struct timeval	*last_eat;
	t_main			*main;
}				t_philo;

int			quit_prog(char *str);
void		free_all(t_main *main);
long long	ft_atoi_philo(const char *str);

#endif