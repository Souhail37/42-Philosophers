/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:39:05 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/21 14:24:45 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_number
{
	long	start;
	int		numb_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		notepme;
}	t_number;

typedef struct s_philo
{
	int				index;
	long			last_time;
	int				number_of_eating;
	pthread_t		philo;
	t_number		numbers;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	*print;
}	t_philo;

typedef struct s_data
{
	char			*str;
	char			**spl;
	t_number		numbers;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}	t_data;

int		ft_atoi(char *str);
int		ft_isdigit(char **str);
int		is_max_int(char **av, int ac);
long	ft_atol(char *str);
size_t	ft_strlen(char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *buffers, char *buff, char c);
void	ft_joinargs(char **str, char **av);
void	ft_philo(t_data *var);
long	ft_gettime(void);
void	ft_init(t_data *var, char **spl);
void	checker_thread(t_data *var);
void	*ft_checker(void *data);
long	ft_gettime(void);
void	ft_time(int number);

#endif