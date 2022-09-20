/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:33:13 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/20 22:46:30 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_n(long n, t_data *var)
{
	if (n > var->philo->numbers.time_to_die)
	{
		sem_wait(var->print);
		printf("%ld philo number %d %s\n",
			ft_gettime() - var->philo->numbers.start, var->philo->index, "die");
		return (0);
	}
	return (1);
}

void	*ft_checker(void *data)
{
	t_data	*var;
	long	n;

	var = (t_data *)data;
	while (var->philo->status)
	{
		n = ft_gettime() - var->philo->last_time;
		if (!check_n(n, var))
			exit (var->philo->index);
		var->philo->eating += (var->philo->numbers.notepme > 0
				&& var->philo->number_of_eating >= var->philo->numbers.notepme);
		if (var->philo->eating == var->philo->numbers.numb_of_philo)
		{
			var->philo->status = 0;
			break ;
		}
	}
	return (NULL);
}
