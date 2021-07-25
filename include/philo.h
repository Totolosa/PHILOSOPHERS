#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_eat_philo
{
	int				n_eat;
	struct timeval	last_eat;
	pthread_mutex_t	lock;
	int				done;
}				t_eat_philo;

typedef struct	s_main
{
	long long		nbr_philo;
	pthread_t		*tread_philo;
	t_eat_philo		*eat_philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				*philos_done;
	int				done;
	long			time_die;
	long long		time_eat;
	long long		time_sleep;
	long long		eat_max;
	struct timeval	start;
	int				dead;
	int				*i;
	int				code_out;
}				t_main;

typedef struct	s_num_philo
{
	int				i;
	t_main			*main;
}				t_num_philo;

int			quit_prog(char *str);
void		free_all(t_main *main);
long long	ft_atoi_philo(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_putstr_fd(char *s, int fd);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *s);

#endif