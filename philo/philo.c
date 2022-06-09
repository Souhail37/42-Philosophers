/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:52:19 by sismaili          #+#    #+#             */
/*   Updated: 2022/06/08 19:45:42 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	a = 0;
pthread_mutex_t	mutex;

void	btata()
{
	int		i;

	i = 1;
	a = 0;
	while (i < 500000)
	{
		pthread_mutex_lock(&mutex);
		a = a + i;
		i++;
		pthread_mutex_unlock(&mutex);
	}
}

void	test()
{
	int		i;

	i = 500000;
	a = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		a = a + i;
		i++;
		pthread_mutex_unlock(&mutex);
	}
}

int	valid_arg(char **av)
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
			write(2, "Error\n", 6);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	t1[6];
	int		i;

	i = 1;
	if (ac == 5)
	{
		if (valid_arg(av + 1))
			return (0);
		ft_joinargs(&data.str, av);
		data.spl = ft_split(data.str, ' ');
		if (!ft_isdigit(data.spl))
			return (1);
		a = 0;
		pthread_mutex_init(&mutex, NULL);
		while (i <= ft_atoi(data.spl[0]))
		{
			pthread_create(t1 + i, NULL, (void*)btata, NULL);
			printf("lfaylassof %d khda l3ayba\n", i);
			usleep(500);
			printf("lfaylassof %d ki 9assi\n", i);
			usleep(500);
			printf("lfaylassof %d na3ess\n", i);
			usleep(500);
			printf("lfaylassof %d ki fakar\n", i);
			usleep(500);
			printf("lfaylassof %d ina lilah a dahmad\n", i);
			usleep(500);
			pthread_join(t1[i], NULL);
			i++;
		}
		printf("%ld\n", a);
		pthread_mutex_destroy(&mutex);
	}
	return (0);
}