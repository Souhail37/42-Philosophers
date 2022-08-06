/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: newgate <newgate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:39:05 by sismaili          #+#    #+#             */
/*   Updated: 2022/08/04 15:47:50 by newgate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_f_mutex
{
	pthread_mutex_t	fork;
	int				f_status;
}	t_mutex;

typedef struct s_number
{
	int		numb_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		notepme;
}	t_number;

typedef struct s_philo
{
	int			index;
	int			last_time;
	int			number_of_eating_times;
	t_number	*numbers;
	t_mutex		fork;
	t_mutex		*next_fork;
}	t_philo;

typedef struct s_data
{
	char		*str;
	char		**spl;
	t_number	numbers;
	t_philo		*philo;
}	t_data;

int		ft_atoi(char *str);
int		ft_isdigit(char **str);
int		is_max_int(char **av, int ac);
long	ft_atol(char *str);
size_t	ft_strlen(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *buffers, char *buff, char c);
void	ft_joinargs(char **str, char **av);
void    ft_philo(t_data *var);

#endif