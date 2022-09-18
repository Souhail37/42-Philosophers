/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:08:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/18 17:15:22 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printf_sem(char *str, t_data *var)
{
	sem_wait(&var->print);
	printf("%ld philo number %d %s\n",
		ft_gettime() - var->philo->numbers.start, var->philo->index, str);
	sem_post(&var->print);
}

void	*philo_fun(t_data *var)
{
	pthread_t	checker;

	if (pthread_create(&checker, NULL, &ft_checker, var) != 0)
	{
		free (checker);
		return (NULL);
	}
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
	if (pthread_join(checker, NULL) != 0)
	{
		free (checker);
		return (NULL);
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
			printf("Error in fork !\n");
			exit(EXIT_FAILURE);
		}
		if (var->philo->pid[i] == 0)
		{
			var->philo->index = i + 1;
			var->philo->last_time = ft_gettime();
			philo_fun(var);
		}
		i++;
	}
}
