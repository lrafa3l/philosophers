/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:11:01 by lrafael           #+#    #+#             */
/*   Updated: 2025/01/25 08:29:32 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pthread_m_destroy(t_list *data)
{
	pthread_mutex_destroy(&data->fork);
	pthread_mutex_destroy(&data->stop);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->satisfied);
	pthread_mutex_destroy(&data->print);
}

int	ft_init(int argc, char *argv[])
{
	t_list	*data;

	data = NULL;
	if (ft_atoi(argv[1]) == 1)
	{
		data = insert(data, 1, NULL);
		data = init_data(argc, argv, data);
		if (!data)
			return (1);
		pthread_create(&data->philo, NULL, philo, (void *)data);
		pthread_join(data->philo, NULL);
		pthread_m_destroy(data);
	} 
	else
	{
		data = init(argc, argv, data);
		if (!data)
			return (1);
		data = update_data(argc, argv, data);
		t_list *temp = data;
		do {
			printf("Philo %d:\ntime_to_die=%ld, time_to_eat=%ld, time_to_sleep=%ld, times_each_philo_must_eat=%ld\n",
				   temp->id, temp->time_to_die, temp->time_to_eat, temp->time_to_sleep, temp->times_each_philo_must_eat);
			temp = temp->next;
		} while (temp != data);
		pthreads_create(data);
		pthreads_join(data);
		pthreads_m_destroy(data);
	}
	data = delete (data);
	return (0);
}

static void	init_one_mutexes(t_list *data)
{
	pthread_mutex_init(&data->fork, NULL);
	pthread_mutex_init(&data->stop, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->satisfied, NULL);
	pthread_mutex_init(&data->print, NULL);
}

t_list	*init_data(int argc, char *argv[], t_list *data)
{
	if (!check_args(argc, argv))
	{
		printf("./philo n_philos time_to_die time_to_eat ");
		printf("time_to_sleep times_each_philosopher_must_eat\n");
		return (NULL);
	}
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->times_each_philo_must_eat = -1;
	if (argc == 6)
		data->times_each_philo_must_eat = ft_atoi(argv[5]);
	data->last_meal = current_time();
	data->start_time = current_time();
	data->died = 0;
	data->eating = 0;
	data->stopp = 0;
	data->philo = 0;
	init_one_mutexes(data);
	return (data);
}
