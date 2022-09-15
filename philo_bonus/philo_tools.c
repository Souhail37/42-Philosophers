/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:08:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/15 14:44:28 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(char *str, t_philo philo)
{
	pthread_mutex_lock(philo.print);
	printf("%ld philo number %d %s\n",
		ft_gettime() - philo.numbers.start, philo.index, str);
	pthread_mutex_unlock(philo.print);
}

void	*thread_fun(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(philo->fork);
		pthread_mutex_lock(philo->next_fork);
		printf_mutex("takes first fork", *philo);
		printf_mutex("takes second fork", *philo);
		printf_mutex("is eating", *philo);
		philo->last_time = ft_gettime();
		if (philo->numbers.notepme > 0)
			philo->number_of_eating++;
		ft_time(philo->numbers.time_to_eat);
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next_fork);
		printf_mutex("is sleeping", *philo);
		ft_time(philo->numbers.time_to_sleep);
		printf_mutex("is thinking", *philo);
	}
	return (NULL);
}

void	ft_philo(t_data *var)
{
	int			i;

	i = 0;
	ft_init(var, var->spl);
	while (i < var->numbers.numb_of_philo)
	{
		if (pthread_create(&var->philo[i].philo, NULL,
				&thread_fun, &var->philo[i]) != 0)
		{
			free (var->philo[i].philo);
			return ;
		}
		pthread_detach(var->philo[i].philo);
		i++;
	}
	checker_thread(var);
}
