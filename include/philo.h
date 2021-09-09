/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 20:01:55 by tdayde            #+#    #+#             */
/*   Updated: 2021/09/09 20:15:26 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/sem.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_eat_philo
{
	int				n_eat;
	struct timeval	last_eat;
	pthread_mutex_t	lock;
	int				done;
}				t_eat_philo;

typedef struct s_main
{
	long long		nbr_philo;
	pthread_t		*tread_philo;
	pthread_mutex_t	*fork_mut;
	pthread_mutex_t	print_mut;
	int				dead;
	sem_t			*fork_sem;
	sem_t			*print_sem;
	sem_t			*start_sem;
	pthread_t		*end_main;
	pid_t			*pid_forks;
	int				i;
	t_eat_philo		*eat_philo;
	int				*philos_done;
	int				philos_done_sem;
	int				done;
	long			time_die;
	long long		time_eat;
	long long		time_sleep;
	long long		eat_max;
	struct timeval	start;
	int				code_out;
}				t_main;

typedef struct s_num_philo
{
	int				i;
	t_main			*main;
}				t_num_philo;

int			check_args(int argc, char **argv, t_main *main);
int			init(t_main *main);
int			init_philo(int i, t_num_philo **philo, t_main *main);
void		*philosopher_life(void *arg);
void		print_str_mutex(char *str, int i, t_main *main);
int			time_diff(struct timeval *start);

void		philosopher_life_bonus(t_main *main);
void		print_str_sem(char *str, int i, t_main *main);
void		*analyse_philo_proces(void *arg);

int			quit_prog(char *str);
void		free_all(t_main *main);
void		free_all_bonus(t_main *main);
long long	ft_atoi_philo(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_putstr_fd(char *s, int fd);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *s);

#endif