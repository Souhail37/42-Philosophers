/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:01:25 by sismaili          #+#    #+#             */
/*   Updated: 2022/06/08 19:23:46 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(char **spl)
{
	int	i;
	int	j;

	i = 0;
	while (spl[i])
	{
		j = 0;
		while(spl[i][j])
		{
			if (spl[i][j] == '+' || spl[i][j] == '-')
				j++;
			if (spl[i][j] < 48 || spl[i][j] > 57)
			{
				write(2, "Error\n", 6);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
