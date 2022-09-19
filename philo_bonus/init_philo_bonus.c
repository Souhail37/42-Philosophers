/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:26:08 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/19 15:40:02 by sismaili         ###   ########.fr       */
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
	var->philo->numbers = var->numbers;
	var->philo->status = 1;
	var->philo->number_of_eating = 0;
	var->philo->numbers.start = ft_gettime();
	var->philo->last_time = var->philo->numbers.start;
	var->philo->index = 1;
}

void	ft_init(t_data *var, char **spl)
{
	init_numbers(var, spl);
	var->philo = malloc(sizeof(t_philo) * var->numbers.numb_of_philo);
	if (!var->philo)
		return ;
	sem_unlink("forks");
	var->forks = sem_open("forks", O_CREAT, 0644, var->numbers.numb_of_philo);
	init_philosophers(var);
}
