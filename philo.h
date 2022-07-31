/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:39:05 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/31 22:29:05 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	char	*str;
	char	**spl;
	int		numb_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		notepme;
}	t_philo;

int		ft_atoi(char *str);
int		ft_isdigit(char **str);
int		is_max_int(char **av, int ac);
long	ft_atol(char *str);
size_t	ft_strlen(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *buffers, char *buff, char c);
void	ft_joinargs(char **str, char **av);

#endif