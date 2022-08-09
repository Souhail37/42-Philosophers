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
	var->numbers.start = ft_gettime();
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
	int		check;

	philo = data;
	check = 0;
	while (philo->checker.status)
	{
		if (ft_gettime() - philo->last_time >= philo->numbers->time_to_die)
		{
			printf("philo number %d died\n", philo->index);
			philo->checker.status = 0;
		}
		if (philo->numbers->notepme > 0 && check < philo->numbers->notepme)
			check++;
	}
	if (check == philo->numbers->notepme)
		philo->checker.status = 0;
	return (NULL);
}

void	*thread_fun(void *data)
{
	t_philo	*philo;

	philo = data;
	while (philo->checker.status)
	{
		pthread_mutex_lock(philo->fork);
		pthread_mutex_lock(philo->next_fork);
		printf("%ld philo number %d takes first fork\n", ft_gettime() - philo->numbers->start, philo->index);
		printf("%ld philo number %d takes second fork\n", ft_gettime() - philo->numbers->start, philo->index);
		printf("%ld philo number %d bda l9ass\n", ft_gettime() - philo->numbers->start, philo->index);
		philo->last_time = ft_gettime();
		ft_time(philo->numbers->time_to_eat);
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next_fork);
		printf("%ld philo number %d n3ass\n", ft_gettime() - philo->numbers->start, philo->index);
		ft_time(philo->numbers->time_to_sleep);
		printf("%ld philo number %d is thinking\n", ft_gettime() - philo->numbers->start, philo->index);
		// if (philo.fork.f_status == 0 && philo.next_fork->f_status == 0)
		// {
		// 	philo.fork.f_status = 1;
		// 	philo.next_fork->f_status = 1;
		// 	pthread_mutex_lock(&philo.fork.fork);
		// 	printf("philo number %d takes first fork\n", philo.index);
		// 	pthread_mutex_lock(&philo.next_fork->fork);
		// 	printf("philo number %d takes second fork\n", philo.index);
		// 	printf("philo number %d bda l9ass\n", philo.index);
		// 	philo.last_time = ft_gettime();
		// 	ft_time(philo.numbers->time_to_eat);
		// 	philo.fork.f_status = 0;
		// 	philo.next_fork->f_status = 0;
		// 	pthread_mutex_unlock(&philo.fork.fork);
		// 	pthread_mutex_unlock(&philo.next_fork->fork);
		// 	printf("philo number %d n3ass\n", philo.index);
		// 	ft_time(philo.numbers->time_to_sleep);
		// }
		// else
		// {
		// 	while (philo.fork.f_status == 1 && philo.next_fork->f_status == 1)
		// 			printf("philo number %d is thinking\n", philo.index);
		// 	if (philo.fork.f_status == 0 && philo.next_fork->f_status == 1)
		// 	{
		// 		pthread_mutex_lock(&philo.fork.fork);
		// 		philo.fork.f_status = 1;
		// 		printf("philo number %d takes first fork\n", philo.index);
		// 		pthread_mutex_lock(&philo.next_fork->fork);
		// 		philo.next_fork->f_status = 1;
		// 		printf("philo number %d takes second fork\n", philo.index);
		// 	}
		// 	else if (philo.next_fork->f_status == 0 && philo.fork.f_status == 1)
		// 	{
		// 		pthread_mutex_lock(&philo.next_fork->fork);
		// 		philo.next_fork->f_status = 1;
		// 		printf("philo number %d takes first fork\n", philo.index);
		// 		pthread_mutex_lock(&philo.fork.fork);
		// 		philo.fork.f_status = 1;
		// 		printf("philo number %d takes second fork\n", philo.index);
		// 	}
		// 	printf("philo number %d bda l9ass\n", philo.index);
		// 	philo.last_time = ft_gettime();
		// 	ft_time(philo.numbers->time_to_eat);
		// 	philo.fork.f_status = 0;
		// 	philo.next_fork->f_status = 0;
		// 	pthread_mutex_unlock(&philo.fork.fork);
		// 	pthread_mutex_unlock(&philo.next_fork->fork);
		// 	printf("philo number %d n3ass\n", philo.index);
		// 	ft_time(philo.numbers->time_to_sleep);
		// }
	}
	return (NULL);
}

void	ft_philo(t_data *var)
{
	pthread_t	*th;
	int			i;

	i = 0;
	ft_init(var, var->spl);
	th = malloc(sizeof(pthread_t) * var->numbers.numb_of_philo);
	var->philo->checker.checker = malloc(sizeof(pthread_t) * var->numbers.numb_of_philo);
	if (!th || !var->philo->checker.checker)
		return ;
	var->philo->numbers = &var->numbers;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].numbers = &var->numbers;
		var->philo[i].checker.status = 1;
		i++;
	}
	i = 0;
	// while (i < var->numbers.numb_of_philo)
	// {
	// 	var->philo[i].numbers->start = ft_gettime();
	// 	i++;
	// }
	// i = 0;
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
	i = 0;
	while (i < var->numbers.numb_of_philo)
	{
		if (pthread_create(&var->philo->checker.checker[i], NULL, &ft_checker, &var->philo[i]) != 0)
		{
			free (var->philo->checker.checker);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < var->numbers.numb_of_philo)
	{
		if (pthread_join(var->philo->checker.checker[i], NULL) != 0)
		{
			free (var->philo->checker.checker);
			return ;
		}
		i++;
	}
	printf("we are done !!\n");
}