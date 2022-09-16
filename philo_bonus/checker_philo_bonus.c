/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:33:13 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/15 20:53:37 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_n(long n, t_philo *philo, int i)
{
	if (n >= philo[i].numbers.time_to_die)
	{
		sem_wait(philo[i].print);
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
	int		dided;

	philo = (t_philo *)data;
	while (philo->status)
	{
		i = 0;
		dided = 0;
		while (i < philo->numbers.numb_of_philo)
		{
			n = ft_gettime() - philo[i].last_time;
			if (!check_n(n, philo, i))
				return (0);
			dided += (philo[i].numbers.notepme > 0
					&& philo[i].number_of_eating >= philo[i].numbers.notepme);
			i++;
		}
		if (dided == philo->numbers.numb_of_philo)
			break ;
	}
	return (NULL);
}

// void	checker_thread(t_data *var)
// {
// 	pthread_t	checker;

// 	if (pthread_create(&checker, NULL, &ft_checker, var->philo) != 0)
// 	{
// 		free (checker);
// 		return ;
// 	}
// 	if (pthread_join(checker, NULL) != 0)
// 	{
// 		free (checker);
// 		return ;
// 	}
// }