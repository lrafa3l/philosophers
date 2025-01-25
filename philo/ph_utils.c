/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:49:19 by lrafael           #+#    #+#             */
/*   Updated: 2025/01/23 12:49:36 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char *av[])
{
	int	i;
	int	j;

	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (!(av[i][j] >= 48 && av[i][j] <= 57) || ft_atoi(av[i]) < 1)
				return (0);
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

long int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (str && *str >= 48 && *str <= 57)
	{
		result *= 10;
		result += *str - 48;
		str++;
	}
	return (result * sign);
}

long int	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_list	*first_philo(t_list *data)
{
	t_list	*aux;

	aux = data->next;
	if (data->id == 1)
		return (data);
	while (aux != data)
	{
		if (aux->id == 1)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}
