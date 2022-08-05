/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: newgate <newgate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:08:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/08/04 16:01:53 by newgate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_data *var, char **spl)
{
	int	i;

	i = 0;
	var->numbers.numb_of_philo = ft_atoi(spl[0]);
	var->numbers.time_to_die = ft_atoi(spl[1]);
	var->numbers.time_to_eat = ft_atoi(spl[2]);
	var->numbers.time_to_sleep = ft_atoi(spl[3]);
	if (spl[4])
		var->numbers.notepme = ft_atoi(spl[4]);
	var->philo = malloc(sizeof(t_philo) * var->numbers.numb_of_philo);
	if (!var->philo)
		return ;
	while (i < var->numbers.numb_of_philo)
	{
		pthread_mutex_init(&var->philo[i].fork.fork, NULL);
		i++;
	}
	i = 0;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].next_fork = &var->philo[(i + 1) % var->numbers.numb_of_philo].fork;
		i++;
	}
}

void	*thread_fun(void *data)
{
	t_philo	philo;

	philo = *(t_philo *)data;
	if (philo.fork.f_status == 0)
	{
		pthread_mutex_lock(&philo.fork.fork);
		philo.fork.f_status = 1;
		printf("philo number %d takes first fork\n", philo.index);
	}
	if (philo.next_fork->f_status == 0)
	{
		pthread_mutex_lock(&philo.next_fork->fork);
		philo.next_fork->f_status = 1;
		printf("philo number %d takes second fork\n", philo.index);
		printf("philo number %d bda l9ass\n", philo.index);
		usleep(200);
		// philo.fork.f_status = 0;
		// philo.next_fork->f_status = 0;
	}
	pthread_mutex_unlock(&philo.fork.fork);
	pthread_mutex_unlock(&philo.next_fork->fork);
	return (NULL);
}

void	ft_philo(t_data *var)
{
	pthread_t	*th;
	int			i;

	i = 0;
	ft_init(var, var->spl);
	th = malloc(sizeof(pthread_t) * var->numbers.numb_of_philo);
	if (!th)
		return ;
	var->philo->numbers = &var->numbers;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].index = i + 1;
		if (pthread_create(&th[i], NULL, &thread_fun, &var->philo[i]) != 0)
		{
			free (th);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < var->numbers.numb_of_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			free (th);
			return ;
		}
		i++;
	}
	printf("we are done !!\n");
}