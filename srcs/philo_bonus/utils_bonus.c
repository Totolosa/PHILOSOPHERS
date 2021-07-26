#include "philo.h"

int	time_diff(struct timeval *start)
{
	long			res;
	struct timeval	now;

	gettimeofday(&now, NULL);
	res = (now.tv_sec - start->tv_sec) * 1000
		+ (now.tv_usec - start->tv_usec) / 1000;
	return (res);
}

void	print_str_sem(char *str, int i, t_main *main)
{
	sem_wait(main->print_sem);
	printf("%d : %d %s\n", time_diff(&main->start), i, str);
	sem_post(main->print_sem);
}
