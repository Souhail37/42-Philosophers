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

void	printf_mutex(char *str, t_philo *philo)
{
	pthread_mutex_t	print;

	pthread_mutex_lock(&print);
	printf("%ld philo number %d %s\n", ft_gettime() - philo->numbers->start, philo->index, str);
	pthread_mutex_unlock(&print);
}

void	ft_init(t_data *var, char **spl)
{
	int	i;

	i = 0;
	var->numbers.start = ft_gettime();
	var->numbers.numb_of_philo = ft_atoi(spl[0]);
	var->numbers.time_to_die = ft_atoi(spl[1]);
	var->numbers.time_to_eat = ft_atoi(spl[2]);
	var->numbers.time_to_sleep = ft_atoi(spl[3]);
	if (spl[4])
		var->numbers.notepme = ft_atoi(spl[4]);
	else
		var->numbers.notepme = 0;
	var->philo = malloc(sizeof(t_philo) * var->numbers.numb_of_philo);
	var->forks = malloc(sizeof(pthread_mutex_t) * var->numbers.numb_of_philo);
	if (!var->philo || !var->forks)
		return ;
	while (i < var->numbers.numb_of_philo)
	{
		pthread_mutex_init(&var->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].fork = &var->forks[i];
		var->philo[i].next_fork = &var->forks[(i + 1) % var->numbers.numb_of_philo];
		i++;
	}
}

long	ft_gettime()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_time(long number)
{
	long	start;

	start = ft_gettime();
	while (ft_gettime() - start < number)
		usleep(50);
}

void	*ft_checker(void *data)
{
	t_philo	*philo;
	int		checker;
	int		counter;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	while (i < philo->numbers->numb_of_philo)
	{
		checker = 1;
		counter = 0;
		while (checker)
		{
			if (ft_gettime() - philo->last_time >= philo->numbers->time_to_die)
			{
				printf_mutex("died", philo);
				checker = 0;
				return (NULL);
			}
			if (philo->numbers->notepme > 0 && counter <= philo->numbers->notepme)
			{
				counter++;
				if (counter == philo->numbers->notepme)
				{
					checker = 0;
					return (NULL);
				}
			}
		}
		i++;
	}
	return (NULL);
}

void	*thread_fun(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->checker.status)
	{
		pthread_mutex_lock(philo->fork);
		pthread_mutex_lock(philo->next_fork);
		printf_mutex("takes first fork", philo);
		printf_mutex("takes second fork", philo);
		printf_mutex("is eating", philo);
		philo->last_time = ft_gettime();
		ft_time(philo->numbers->time_to_eat);
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next_fork);
		printf_mutex("is sleeping", philo);
		ft_time(philo->numbers->time_to_sleep);
		printf_mutex("is thinking", philo);
	}
	return (NULL);
}

void	ft_philo(t_data *var)
{
	pthread_t	*th;
	pthread_t	checker;
	int			i;

	i = 0;
	ft_init(var, var->spl);
	th = malloc(sizeof(pthread_t) * var->numbers.numb_of_philo);
	checker = malloc(sizeof(pthread_t) * var->numbers.numb_of_philo);
	if (!th || !checker)
		return ;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].numbers = &var->numbers;
		var->philo[i].checker.status = 1;
		i++;
	}
	i = 0;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].index = i + 1;
		if (pthread_create(&th[i], NULL, &thread_fun, &var->philo[i]) != 0)
		{
			free (th);
			return ;
		}
		pthread_detach(th[i]);
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
	printf("we are done !!\n");
}