/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:45:59 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/31 22:27:17 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '+')
				j++;
			if (str[i][j] < 48 || str[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_max_int(char **av, int ac)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (ft_atol(av[i]) > 2147483647)
			return (0);
		i++;
	}
	return (1);
}
