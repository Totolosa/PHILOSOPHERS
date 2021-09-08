/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:49:42 by tdayde            #+#    #+#             */
/*   Updated: 2021/09/08 19:50:25 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*end_philo(void *arg)
{
	t_num_philo	*philo;
	int			res;
	int			j;

	philo = (t_num_philo *)arg;
	waitpid(philo->main->pid_forks[philo->i], &res, WEXITSTATUS(res));
	if (res == 256)
	{
		philo->main->dead = 1;
		j = -1;
		while (++j < philo->main->nbr_philo)
			if (j != philo->i)
				kill(philo->main->pid_forks[j], SIGKILL);
	}
	else if (res == 512)
		philo->main->philos_done_sem++;
	return (NULL);
}

int	end_main(t_main *main)
{
	int			i;
	t_num_philo	*philo;

	i = 0;
	philo = NULL;
	main->end_main = ft_calloc(main->nbr_philo, sizeof(pthread_t));
	if (!main->tread_philo)
		return (quit_prog("Malloc main->end_main error\n"));
	while (i < main->nbr_philo)
	{
		if (init_philo(i, &philo, main))
			return (1);
		if (pthread_create(&main->end_main[i++], NULL,
				&end_philo, philo) != 0)
			return (quit_prog("ERROR pthread_create\n"));
	}
	i = 0;
	while (i < main->nbr_philo)
		if (pthread_join(main->end_main[i++], NULL) != 0)
			return (quit_prog("ERROR pthread_join\n"));
	if (!main->dead && main->philos_done_sem == main->nbr_philo)
		printf("ALL PHILOSOPHERS ARE SATED!\n");
	return (0);
}

int	philo_forks(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->nbr_philo)
	{
		main->pid_forks[i] = fork();
		if (main->pid_forks[i] == 0)
		{
			main->i = i;
			if (pthread_create(&main->tread_philo[i++], NULL,
					&analyse_philo_proces, main) != 0)
				return (quit_prog("ERROR pthread_create\n"));
			philosopher_life_bonus(main);
		}
	}
	i = -1;
	while (++i < main->nbr_philo)
		sem_post(main->start_sem);
	end_main(main);
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
	else if (philo_forks(&main))
		main.code_out = 1;
	free_all_bonus(&main);
	return (main.code_out);
}
