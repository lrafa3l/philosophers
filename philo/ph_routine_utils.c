/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:56:10 by lrafael           #+#    #+#             */
/*   Updated: 2025/01/24 11:34:33 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_satisfied(t_list *data, t_list *aux, t_list *first)
{
	first = first_philo(data);
	pthread_mutex_lock(&first->satisfied);
	if (data->times_each_philo_must_eat == -1)
	{
		pthread_mutex_unlock(&first->satisfied);
		return (0);
	}
	if (data->times_each_philo_must_eat > 0)
	{
		pthread_mutex_unlock(&first->satisfied);
		return (0);
	}
	aux = data->next;
	while (aux != data)
	{
		if (aux->times_each_philo_must_eat > 0)
		{
			pthread_mutex_unlock(&first->satisfied);
			return (0);
		}
		aux = aux->next;
	}
	pthread_mutex_unlock(&first->satisfied);
	return (1);
}

int	ft_death(t_list *data)
{
	t_list	*first;
	t_list	*aux;

	first = first_philo(data);
	pthread_mutex_lock(&first->death);
	if (data->died != 0)
	{
		pthread_mutex_unlock(&first->death);
		return (1);
	}
	aux = data->next;
	while (aux != data)
	{
		if (aux->died != 0)
		{
			pthread_mutex_unlock(&first->death);
			return (1);
		}
		aux = aux->next;
	}
	pthread_mutex_unlock(&first->death);
	return (0);
}

int	ft_stop(t_list *data)
{
	t_list	*first;

	first = first_philo(data);
	pthread_mutex_lock(&first->stop);
	if (ft_satisfied(data, NULL, NULL) == 1)
	{
		pthread_mutex_unlock(&first->stop);
		return (1);
	}
	if (ft_death(data) == 1)
	{
		pthread_mutex_unlock(&first->stop);
		return (1);
	}
	pthread_mutex_unlock(&first->stop);
	return (0);
}

void	print_msg(t_list *data, char *str)
{
	if (ft_strcmp(str, "think") == 0)
		printf("[%ld] philo %d is thinking\n", current_time()
			- data->start_time, data->id);
	else if (ft_strcmp(str, "take fork") == 0)
		printf("[%ld] philo %d has taken a fork\n", current_time()
			- data->start_time, data->id);
	else if (ft_strcmp(str, "died") == 0)
		printf("[%ld] philo %d died\n", current_time() - data->start_time,
			data->id);
	else if (ft_strcmp(str, "eat") == 0)
		printf("[%ld] philo %d is eating\n", current_time() - data->start_time,
			data->id);
	else if (ft_strcmp(str, "sleep") == 0)
		printf("[%ld] philo %d is sleeping\n", current_time()
			- data->start_time, data->id);
}

t_list	*print_s(t_list *data, char *str)
{
	t_list	*first;

	first = first_philo(data);
	pthread_mutex_lock(&first->print);
	if (ft_stop(data) == 1)
	{
		if (first->stopp == 1)
		{
			pthread_mutex_unlock(&first->print);
			return (data);
		}
		if (first->died == 1)
		{
			pthread_mutex_unlock(&first->print);
			return (data);
		}
		print_msg(data, str);
		first->stopp = 1;
		first->died = 1;
		pthread_mutex_unlock(&first->print);
		return (data);
	}
	print_msg(data, str);
	pthread_mutex_unlock(&first->print);
	return (data);
}
