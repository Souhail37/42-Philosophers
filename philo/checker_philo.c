/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:33:13 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/20 15:31:41 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_n(long n, t_philo *philo, int i)
{
	if (n >= philo[i].numbers.time_to_die)
	{
		pthread_mutex_lock(philo[i].print);
		printf("%ld philo number %d %s\n",
			ft_gettime() - philo[i].numbers.start, philo[i].index, "die");
		return (0);
	}
	return (1);
}

void	*ft_checker(void *data)
{
	t_philo	*philo;
	long	n;
	int		i;
	int		eating;

	philo = (t_philo *)data;
	while (philo->status)
	{
		i = 0;
		eating = 0;
		while (i < philo->numbers.numb_of_philo)
		{
			n = ft_gettime() - philo[i].last_time;
			if (!check_n(n, philo, i))
				return (0);
			eating += (philo[i].numbers.notepme > 0
					&& philo[i].number_of_eating >= philo[i].numbers.notepme);
			i++;
		}
		if (eating == philo->numbers.numb_of_philo)
			break ;
	}
	return (NULL);
}

void	checker_thread(t_data *var)
{
	pthread_t	checker;

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
