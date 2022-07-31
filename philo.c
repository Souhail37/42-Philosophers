/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:53:39 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/31 22:28:17 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_errors(char **av)
// {
// 	int	i;

// 	i = 0;
// 	while (av[i])
// 	{
// 		if (!ft_isdigit(av[i]) || !is_max_int())
// 		{
// 			write(2, "error\n", 6);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

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
	t_philo	ph;
	int		i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		write(2, "error! Invalid arguments\n", 25);
		return (0);
	}
	if (!valid_args(av + 1))
		return (0);
	ft_joinargs(&ph.str, av);
	ph.spl = ft_split(ph.str, ' ');
	while (ph.spl[i])
		i++;
	if (!ft_isdigit(ph.spl) || !is_max_int(ph.spl, i))
	{
		write(2, "error\n", 6);
		return (0);
	}
	return (0);
}
