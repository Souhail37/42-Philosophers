/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:26:08 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/17 19:53:02 by sismaili         ###   ########.fr       */
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

static void	init_philosophers(t_data *var)
{
	int	i;

	i = 1;
	while (i <= var->numbers.numb_of_philo)
	{
		var->philo[i].numbers = var->numbers;
		var->philo[i].status = 1;
		var->philo[i].number_of_eating = 0;
		var->philo[i].numbers.start = ft_gettime();
		var->philo[i].last_time = var->philo[i].numbers.start;
		var->philo[i].index = i;
		i++;
	}
}

void	ft_init(t_data *var, char **spl)
{
	int		i;

	i = 0;
	init_numbers(var, spl);
	var->philo = malloc(sizeof(t_philo) * var->numbers.numb_of_philo);
	// var->forks = malloc(sizeof(sem_t) * var->numbers.numb_of_philo);
	// print = malloc(sizeof(sem_t) * 1);
	if (!var->philo)
		return ;
	// while (i < var->numbers.numb_of_philo)
	// {
	sem_unlink("forks");
	var->forks = sem_open("forks", O_CREAT, 0644, var->numbers.numb_of_philo);
	// 	i++;
	// }
	// var->print = sem_open("print", O_CREAT, 0644, 1);
	init_philosophers(var);
}
