/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:08:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/08/02 00:14:07 by sismaili         ###   ########.fr       */
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

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->fork);
	printf("philo number %d take first fork\n", philo->index);
	pthread_mutex_lock(&philo->next_fork);
	printf("philo number %d take second fork\n", philo->index);
	
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next_fork);
	return (NULL);
}

void	ft_philo(t_data *var)
{
	pthread_t	*th;
	int			i;

	i = 0;
	ft_init(&var->numbers, var->spl);
	th = malloc(sizeof(pthread_t) * var->numbers.numb_of_philo);
	var->philo = malloc(sizeof(t_philo) * var->numbers.numb_of_philo);
	if (!th || !var->philo)
		return ;
	while (i < var->numbers.numb_of_philo)
	{
		var->philo[i].index = i + 1;
		pthread_mutex_init(&var->philo[i]->fork, NULL);
		pthread_mutex_init(&var->philo[i].next_fork, NULL);
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