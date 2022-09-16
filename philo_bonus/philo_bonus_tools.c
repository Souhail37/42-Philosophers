/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:08:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/15 20:51:59 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printf_sem(char *str, t_philo philo)
{
	sem_wait(philo.print);
	printf("%ld philo number %d %s\n",
		ft_gettime() - philo.numbers.start, philo.index, str);
	sem_post(philo.print);
}

void	*philo_fun(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->fork);
		sem_wait(philo->second_fork);
		printf_sem("takes first fork", *philo);
		printf_sem("takes second fork", *philo);
		printf_sem("is eating", *philo);
		philo->last_time = ft_gettime();
		if (philo->numbers.notepme > 0)
			philo->number_of_eating++;
		ft_time(philo->numbers.time_to_eat);
		sem_post(philo->fork);
		sem_post(philo->second_fork);
		printf_sem("is sleeping", *philo);
		ft_time(philo->numbers.time_to_sleep);
		printf_sem("is thinking", *philo);
	}
	return (NULL);
}

void	ft_philo(t_data *var)
{
	int		i;
	pid_t	pid;

	i = 0;
	ft_init(var, var->spl);
	while (i < var->numbers.numb_of_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_fun(var->philo);
			kill(pid, SIGKILL);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	checker_thread(var);
}
