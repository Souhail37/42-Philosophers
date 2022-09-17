/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:08:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/17 19:53:05 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printf_sem(char *str, t_data *var)
{
	sem_wait(&var->print);
	printf("start = %ld\n", var->philo->numbers.start);
	printf("%ld philo number %d %s\n",
		ft_gettime() - var->philo->numbers.start, var->philo->index, str);
	sem_post(&var->print);
}

void	*philo_fun(t_data *var)
{
	checker_thread(var);
	while (1)
	{
		sem_wait(var->forks);
		sem_wait(var->forks);
		printf_sem("takes first fork", var);
		printf_sem("takes second fork", var);
		printf_sem("is eating", var);
		var->philo->last_time = ft_gettime();
		if (var->philo->numbers.notepme > 0)
			var->philo->number_of_eating++;
		ft_time(var->philo->numbers.time_to_eat);
		sem_post(var->forks);
		sem_post(var->forks);
		printf_sem("is sleeping", var);
		ft_time(var->philo->numbers.time_to_sleep);
		printf_sem("is thinking", var);
	}
	return (NULL);
}

void	ft_philo(t_data *var)
{
	int		i;

	i = 0;
	ft_init(var, var->spl);
	var->philo->pid = malloc(sizeof(pid_t) * var->numbers.numb_of_philo);
	if (!var->philo->pid)
		return ;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo->pid[i] = fork();
		if (var->philo->pid[i] == -1)
		{
			// var->philo->numbers.start = ft_gettime();
			printf("Error in fork !\n");
			exit(EXIT_FAILURE);
		}
		if (var->philo->pid[i] == 0)
			philo_fun(var);
		i++;
	}
}
