/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:08:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/20 23:09:38 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	printf_sem(char *str, t_data *var)
{
	sem_wait(var->print);
	printf("%ld philo number %d %s\n",
		ft_gettime() - var->philo->numbers.start, var->philo->index, str);
	sem_post(var->print);
}

static void	routine(t_data *var)
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

static void	*philo_fun(t_data *var)
{
	if (pthread_create(&var->checker, NULL, &ft_checker, var) != 0)
	{
		free (var->checker);
		return (NULL);
	}
	while (1)
	{
		routine(var);
		if (var->philo->status == 0)
			exit (0);
	}
	if (pthread_join(var->checker, NULL) != 0)
	{
		free (var->checker);
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
		int id = fork();
		if (id == -1)
		{
			printf("Error in fork !\n");
			exit(EXIT_FAILURE);
		}
		if (id == 0)
		{
			var->philo->index = i + 1;
			var->philo->last_time = ft_gettime();
			philo_fun(var);
		}
		else
			var->philo->pid[i] = id;
		i++;
	}
}
