/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:49:00 by sismaili          #+#    #+#             */
/*   Updated: 2022/09/15 14:51:35 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

size_t	ft_strlen(char *s)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *buffers, char *buff, char c)
{
	int		i;
	int		j;
	char	*new;

	if (!buffers)
	{
		buffers = (char *)malloc(sizeof(char));
		buffers[0] = '\0';
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(buffers)
				+ ft_strlen(buff) + 2));
	if (!new)
		return (0);
	i = -1;
	j = 0;
	while (buffers[++i])
		new[i] = buffers[i];
	new[i++] = c;
	while (buff[j])
		new[i++] = buff[j++];
	new[i] = '\0';
	free (buffers);
	return (new);
}

void	ft_joinargs(char **str, char **av)
{
	int	i;

	*str = NULL;
	i = 1;
	while (av[i])
	{
		*str = ft_strjoin(*str, av[i], ' ');
		i++;
	}
}
