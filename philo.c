/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:53:39 by sismaili          #+#    #+#             */
/*   Updated: 2022/08/01 18:33:05 by sismaili         ###   ########.fr       */
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
	ft_philo(&var);	
	ft_free(&var);
	return (0);
}
