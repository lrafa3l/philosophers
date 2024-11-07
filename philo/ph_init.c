/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:18:47 by lrafael           #+#    #+#             */
/*   Updated: 2024/11/06 11:41:24 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, int argc, char *argv[])
{
	int	i;

	data->philo_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (data->philo_nbr < 2 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->number_of_times_each_philosopher_must_eat == 0)
		return (1);
	data->forks = malloc(sizeof(int) * data->philo_nbr);
	if (!data->forks)
		return (1);
    data->stop_simulation = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->fork_mutex)
	{
		free(data->forks);
		free(data->philos);
		return (1);
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		data->forks[i] = 1;
		if (pthread_mutex_init(&data->fork_mutex[i], NULL))
		{
			free(data->forks);
			free(data->philos);
			free(data->fork_mutex);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		free(data->forks);
		free(data->philos);
		free(data->fork_mutex);
		return (1);
	}
	gettimeofday(&data->start_time, NULL);
	return (0);
}

