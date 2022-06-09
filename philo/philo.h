/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:27:01 by sismaili          #+#    #+#             */
/*   Updated: 2022/06/08 19:45:47 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct data
{
	char			*str;
	char			**spl;
}	t_data;

int		ft_atoi(char *str);
int		ft_isdigit(char **spl);
void	ft_joinargs(char **str, char **av);
char	**ft_split(char *s, char c);

#endif