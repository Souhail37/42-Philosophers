/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:08:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/09 23:35:36 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(char *str, t_philo philo)
{
	pthread_mutex_lock(philo.print);
	printf("%ld philo number %d %s\n", ft_gettime() - philo.numbers.start, philo.index, str);
	pthread_mutex_unlock(philo.print);
}

void	ft_init(t_data *var, char **spl)
{
	int	i;
	pthread_mutex_t *print;

	i = 0;
	var->numbers.numb_of_philo = ft_atoi(spl[0]);
	var->numbers.time_to_die = ft_atoi(spl[1]);
	var->numbers.time_to_eat = ft_atoi(spl[2]);
	var->numbers.time_to_sleep = ft_atoi(spl[3]);
	if (spl[4])
		var->numbers.notepme = ft_atoi(spl[4]);
	else
		var->numbers.notepme = -1;
	var->philo = malloc(sizeof(t_philo) * var->numbers.numb_of_philo);
	var->forks = malloc(sizeof(pthread_mutex_t) * var->numbers.numb_of_philo);
	print = malloc(sizeof(pthread_mutex_t) * 1);
	if (!var->philo || !var->forks || !print)
		return ;
	while (i < var->numbers.numb_of_philo)
	{
		pthread_mutex_init(&var->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(print, NULL);
	i = 0;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].last_time = malloc(sizeof(long));
		var->philo[i].fork = &var->forks[i];
		var->philo[i].next_fork = &var->forks[(i + 1) % var->numbers.numb_of_philo];
		var->philo[i].numbers = var->numbers;
		var->philo[i].status = 1;
		// var->philo[i].number_of_eating_times = var->numbers.notepme;
		var->philo[i].numbers.start = ft_gettime();
		var->philo[i].print = print;
		i++;
	}
}

long	ft_gettime()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_time(int number)
{
	long	start;

	start = ft_gettime();
	while (ft_gettime() - start < number)
		usleep(50);
}

void	*ft_checker(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	while (philo->status)
	{
		i = 0;
		while (i < philo->numbers.numb_of_philo)
		{
			long n = ft_gettime() - *philo[i].last_time;
			if (n >= philo[i].numbers.time_to_die)
			{
				int j = 0;
				pthread_mutex_lock(philo[i].print);
				printf("%ld philo number %d %s\n", ft_gettime() - philo[i].numbers.start, philo[i].index, "die");
				while (j < philo->numbers.numb_of_philo)
					philo[j++].status = 0;
				exit(0);
			}
			if (philo[i].numbers.notepme == 0)
			{
				philo[i].status = 0;
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

void	*thread_fun(void *data)
{
	t_philo	philo;

	philo = *(t_philo *)data;
	while (philo.status)
	{
		pthread_mutex_lock(philo.fork);
		pthread_mutex_lock(philo.next_fork);
		printf_mutex("takes first fork", philo);
		printf_mutex("takes second fork", philo);
		printf_mutex("is eating", philo);
		*philo.last_time = ft_gettime();
		if (philo.numbers.notepme > 0)
			philo.numbers.notepme--;
		ft_time(philo.numbers.time_to_eat);
		pthread_mutex_unlock(philo.fork);
		pthread_mutex_unlock(philo.next_fork);
		printf_mutex("is sleeping", philo);
		ft_time(philo.numbers.time_to_sleep);
		printf_mutex("is thinking", philo);
	}
	return (NULL);
}

void	ft_philo(t_data *var)
{
	pthread_t	checker;
	int			i;

	i = 0;
	ft_init(var, var->spl);
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].index = i + 1;
		*var->philo[i].last_time = ft_gettime();
		if (pthread_create(&var->philo[i].philo, NULL, &thread_fun, &var->philo[i]) != 0)
		{
			free (var->philo[i].philo);
			return ;
		}
		pthread_detach(var->philo[i].philo);
		i++;
	}
	if (pthread_create(&checker, NULL, &ft_checker, var->philo) != 0)
	{
		free (checker);
		return ;
	}
	if (pthread_join(checker, NULL) != 0)
	{
		free (checker);
		return ;
	}
}