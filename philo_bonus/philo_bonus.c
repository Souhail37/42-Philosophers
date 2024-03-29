/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:53:39 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/21 15:22:56 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_free(t_data *var)
{
	int	i;
	int	check;

	i = 0;
	while (var->spl[i])
		free(var->spl[i++]);
	free(var->spl);
	free(var->str);
	if (var->philo)
	{
		free(var->philo);
		waitpid(-1, &check, 0);
		i = -1;
		while (++i < var->numbers.numb_of_philo)
			kill(var->philo->pid[i], SIGKILL);
		free (var->philo->pid);
		sem_close(var->forks);
		sem_close(var->print);
	}
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
	if (ac > 1)
	{
		if (!valid_args(av + 1))
			return (0);
		ft_joinargs(&var.str, av);
		var.spl = ft_split(var.str, ' ');
		while (var.spl[i])
			i++;
		if (i < 4 || i > 5 || !ft_isdigit(var.spl) || !is_max_int(var.spl, i))
		{
			write(2, "error! Invalid arguments\n", 25);
			return (ft_free(&var), 0);
		}
		ft_philo(&var);
		ft_free(&var);
	}
	return (0);
}
