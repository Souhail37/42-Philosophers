/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:33:13 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/18 17:15:10 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_n(long n, t_data *var)
{
	if (n >= var->philo->numbers.time_to_die)
	{
		sem_wait(&var->print);
		printf("%ld philo number %d %s\n",
			ft_gettime() - var->philo->numbers.start, var->philo->index, "die");
		exit (EXIT_FAILURE);
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
			n = ft_gettime() - var->philo->last_time;
			if (!check_n(n, var))
				return (0);
			dided += (var->philo->numbers.notepme > 0
					&& var->philo->number_of_eating >= var->philo->numbers.notepme);
			i++;
		}
		if (dided == var->philo->numbers.numb_of_philo)
			break ;
	}
	return (NULL);
}
