/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:53:39 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/31 23:15:51 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *var)
{
	int	i;

	i = 0;
	while (var->spl[i])
		free(var->spl[i++]);
	free(var->spl);
	free(var->str);
	if (var->philo)
		free(var->philo);
}

int	valid_args(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j] == ' ')
			j++;
		if (av[i][j] == 0)
		{
			write(2, "error\n", 6);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_init(t_philo *philo, char **spl)
{
	philo->numb_of_philo = ft_atoi(spl[0]);
	philo->time_to_die = ft_atoi(spl[1]);
	philo->time_to_eat = ft_atoi(spl[2]);
	philo->time_to_sleep = ft_atoi(spl[3]);
	if (spl[4])
		philo->notepme = ft_atoi(spl[4]);
}

int	main(int ac, char **av)
{
	t_data	var;
	int		i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		write(2, "error! Invalid arguments\n", 25);
		return (0);
	}
	if (!valid_args(av + 1))
		return (0);
	ft_joinargs(&var.str, av);
	var.spl = ft_split(var.str, ' ');
	while (var.spl[i])
		i++;
	if (!ft_isdigit(var.spl) || !is_max_int(var.spl, i))
	{
		write(2, "error\n", 6);
		return (0);
	}
	var.philo = malloc(sizeof(t_philo) * i);
	if (!var.philo)
		return (0);
	ft_init(var.philo, var.spl);
	ft_free(&var);
	return (0);
}
