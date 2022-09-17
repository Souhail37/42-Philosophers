/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:33:13 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/17 19:28:25 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_n(long n, t_data *var, int i)
{
	if (n >= var->philo[i].numbers.time_to_die)
	{
		sem_wait(&var->print);
		printf("%ld philo number %d %s\n",
			ft_gettime() - var->philo[i].numbers.start, var->philo[i].index, "die");
		return (0);
	}
	return (1);
}

void	*ft_checker(void *data)
{
	t_data	*var;
	long	n;
	int		i;
	int		dided;

	var = (t_data *)data;
	while (var->philo->status)
	{
		i = 0;
		dided = 0;
		while (i < var->philo->numbers.numb_of_philo)
		{
			n = ft_gettime() - var->philo[i].last_time;
			if (!check_n(n, var, i))
				return (0);
			dided += (var->philo[i].numbers.notepme > 0
					&& var->philo[i].number_of_eating >= var->philo[i].numbers.notepme);
			i++;
		}
		if (dided == var->philo->numbers.numb_of_philo)
			break ;
	}
	return (NULL);
}

void	checker_thread(t_data *var)
{
	pthread_t	checker;

	if (pthread_create(&checker, NULL, &ft_checker, var) != 0)
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
