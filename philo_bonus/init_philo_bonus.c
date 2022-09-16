/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:26:08 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/15 20:51:32 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_numbers(t_data *var, char **spl)
{
	var->numbers.numb_of_philo = ft_atoi(spl[0]);
	var->numbers.time_to_die = ft_atoi(spl[1]);
	var->numbers.time_to_eat = ft_atoi(spl[2]);
	var->numbers.time_to_sleep = ft_atoi(spl[3]);
	if (spl[4])
		var->numbers.notepme = ft_atoi(spl[4]);
	else
		var->numbers.notepme = -1;
}

static void	init_philosophers(t_data *var, sem_t *print)
{
	int	i;

	i = 1;
	while (i <= var->numbers.numb_of_philo)
	{
		var->philo[i].fork = &var->forks[i - 1];
		var->philo[i].second_fork = &var->forks[i];
		var->philo[i].numbers = var->numbers;
		var->philo[i].status = 1;
		var->philo[i].number_of_eating = 0;
		var->philo[i].numbers.start = ft_gettime();
		var->philo[i].last_time = var->philo[i].numbers.start;
		var->philo[i].print = print;
		var->philo[i].index = i;
		i++;
	}
}

void	ft_init(t_data *var, char **spl)
{
	sem_t	*print;
	int		i;

	i = 0;
	init_numbers(var, spl);
	var->philo = malloc(sizeof(t_philo) * var->numbers.numb_of_philo);
	var->forks = malloc(sizeof(sem_t) * var->numbers.numb_of_philo);
	print = malloc(sizeof(sem_t) * 1);
	if (!var->philo || !var->forks || !print)
		return ;
	while (i < var->numbers.numb_of_philo)
	{
		var->forks = sem_open("forks", O_CREAT, 0644, i);
		i++;
	}
	print = sem_open("print", O_CREAT, 0644, 1);
	init_philosophers(var, print);
}
