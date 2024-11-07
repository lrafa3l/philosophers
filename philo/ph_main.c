/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:01:11 by lrafael           #+#    #+#             */
/*   Updated: 2024/11/07 14:23:50 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!data->stop_simulation || data->number_of_times_each_philosopher_must_eat != 0)
	{
		// Philosopher is hungry and tries to pick up forks
		pthread_mutex_lock(philo->left_fork);
		printf("Philosopher %d picked up left fork\n", philo->id);
		// pthread_mutex_lock(philo->right_fork);
		printf("Philosopher %d picked up right fork\n", philo->id);
		// Philosopher is eating
		printf("Philosopher %d is eating\n", philo->id);
		usleep(data->time_to_eat * 1000);
		// Philosopher puts down forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		// Philosopher is sleeping
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(data->time_to_sleep * 1000);
	}
	data->stop_simulation = 1;
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	gettimeofday(&data->start_time, NULL);
	i = 0;
	while (i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->fork_mutex[i];
		data->philos[i].right_fork = &data->fork_mutex[(i + 1)
			% data->philo_nbr];
		if (pthread_create(&data->philos[i].thread, NULL, &philo_life,
				&data->philos[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (init_data(&data, argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (start_simulation(&data))
	{
		printf("Error: Simulation failed\n");
		return (1);
	}
	clean_up(&data);
	return (0);
}
