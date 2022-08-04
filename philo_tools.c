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

void	ft_init(t_number *numbers, char **spl)
{
	numbers->numb_of_philo = ft_atoi(spl[0]);
	numbers->time_to_die = ft_atoi(spl[1]);
	numbers->time_to_eat = ft_atoi(spl[2]);
	numbers->time_to_sleep = ft_atoi(spl[3]);
	if (spl[4])
		numbers->notepme = ft_atoi(spl[4]);
}


void	*thread_fun(void *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->forks[i]);
	printf("philo number %d take first fork\n", philo->index);
	pthread_mutex_lock(&philo->forks[(i + 1) % philo->numbers.numb_of_philo]);
	printf("philo number %d take second fork\n", philo->index);
	printf("philo number %d bda l9ass\n", philo->index);
	pthread_mutex_unlock(&philo->forks[i]);
	pthread_mutex_unlock(&philo->forks[(i + 1) % philo->numbers.numb_of_philo]);
	i++;
	return (NULL);
}

void	ft_philo(t_data *var)
{
	pthread_t	*th;
	int			i;

	i = 0;
	ft_init(&var->philo->numbers, var->spl);
	th = malloc(sizeof(pthread_t) * var->philo->numbers.numb_of_philo);
	var->philo = malloc(sizeof(t_philo) * var->philo->numbers.numb_of_philo);
	var->philo->forks = malloc (sizeof(pthread_mutex_t) * var->philo->numbers.numb_of_philo);
	if (!th || !var->philo || !var->philo->forks)
		return ;
	while (i < var->philo->numbers.numb_of_philo)
	{
		pthread_mutex_init(&var->philo[i].forks[i], NULL);
		var->philo[i].index = i + 1;
		if (pthread_create(&th[i], NULL, &thread_fun, &var->philo[i]) != 0)
		{
			free (th);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < var->philo->numbers.numb_of_philo)
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