/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:44:28 by lrafael           #+#    #+#             */
/*   Updated: 2025/01/25 11:20:49 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *arg)
{
	t_list	*data;

	data = (t_list *)arg;
	data = print_s(data, "think");
	data = print_s(data, "take fork");
	usleep(data->time_to_die);
	data = print_s(data, "died");
	return (NULL);
}

t_list	*lock_mutexes(t_list *data)
{
	data = print_s(data, "think");
	if (data->id % 2 != 0)
		usleep(100);
	if (data->id % 2 == 0)
	{
		data = print_s(data, "take fork");
		pthread_mutex_lock(&data->fork);
		data = print_s(data, "take fork");
		pthread_mutex_lock(&data->next->fork);
	}
	else
	{
		data = print_s(data, "take fork");
		pthread_mutex_lock(&data->next->fork);
		data = print_s(data, "take fork");
		pthread_mutex_lock(&data->fork);
	}
	return (data);
}

long int	time_from_start(long int start_time)
{
	return (current_time() - start_time);
}

void	ft_sleep(t_list *data, long int sleep_time)
{
	t_list		*first;
	long int	start_time;

	first = first_philo(data);
	start_time = current_time();
	while (time_from_start(start_time) < sleep_time / 1000 && !ft_stop(data))
	{
		if (time_from_start(data->last_meal) > data->time_to_die && data->eating)
		{
			pthread_mutex_lock(&first->death);
			data->died = 1;
			pthread_mutex_unlock(&first->death);
			data = print_s(data, "died");
			return ;
		}
		if (ft_stop(data))
			return ;
		usleep(100);
	}
}

t_list	*ft_eat(t_list *data)
{
	t_list	*first;

	first = first_philo(data);
	print_s(data, "eat");
	data->eating = 1;
	ft_sleep(data, data->time_to_eat);
	data->eating = 0;
	if (!ft_stop(data))
	{
		data->last_meal = time_from_start(data->start_time);
		if (data->times_each_philo_must_eat > 0)
		{
			pthread_mutex_lock(&first->satisfied);
			data->times_each_philo_must_eat--;
			pthread_mutex_unlock(&first->satisfied);
		}
	}
	return (data);
}

void	*philos(void *arg)
{
	t_list	*data;
	t_list	*first;

	data = (t_list *)arg;
	first = first_philo(data);
	data->start_time = current_time();
	while (!ft_stop(data))
	{
		data = lock_mutexes(data);
		if (time_from_start(data->start_time)
			- data->last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&first->death);
			data->died = 1;
			pthread_mutex_unlock(&first->death);
			data = print_s(data, "died");
			break ;
		}
		data = ft_eat(data);
		pthread_mutex_unlock(&data->next->fork);
		pthread_mutex_unlock(&data->fork);
		if (!ft_stop(data))
		{
			data = print_s(data, "sleep");
			ft_sleep(data, data->time_to_sleep);
		}
	}
	return (NULL);
}
