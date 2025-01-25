/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:00:24 by lrafael           #+#    #+#             */
/*   Updated: 2025/01/25 08:26:56 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*init(int argc, char *argv[], t_list *data)
{
	long int	i;
	long int	l;

	if (!check_args(argc, argv))
	{
		printf("./philo n_philos time_to_die time_to_eat ");
		printf("time_to_sleep times_each_philosopher_must_eat\n");
		return (NULL);
	}
	data = NULL;
	i = 0;
	l = ft_atoi(argv[1]);
	while (++i <= l)
	{
		data = insert(data, i, NULL);
		if (!data)
		{
			printf("Error: malloc\n");
			return (NULL);
		}
	}
	return (data);
}

t_list	*update_data(int argc, char *argv[], t_list *data)
{
	t_list	*aux;

	data = init_data(argc, argv, data);
	if (!data)
		return (NULL);
	aux = data->next;
	while (aux != data)
	{
		aux = init_data(argc, argv, aux);
		aux = aux->next;
	}
	return (data);
}

void	pthreads_create(t_list *data)
{
	t_list	*aux;

	pthread_create(&data->philo, NULL, philos, (void *)data);
	aux = data->next;
	while (aux != data)
	{
		pthread_create(&aux->philo, NULL, philos, (void *)aux);
		aux = aux->next;
	}
}

void	pthreads_join(t_list *data)
{
	t_list	*aux;

	pthread_join(data->philo, NULL);
	aux = data->next;
	while (aux != data)
	{
		pthread_join(aux->philo, NULL);
		aux = aux->next;
	}
}

void	pthreads_m_destroy(t_list *data)
{
	t_list	*aux;

	pthread_mutex_destroy(&data->fork);
	pthread_mutex_destroy(&data->stop);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->satisfied);
	pthread_mutex_destroy(&data->print);
	aux = data->next;
	while (aux != data)
	{
		pthread_mutex_destroy(&aux->fork);
		pthread_mutex_destroy(&aux->stop);
		pthread_mutex_destroy(&aux->death);
		pthread_mutex_destroy(&aux->satisfied);
		pthread_mutex_destroy(&aux->print);
		aux = aux->next;
	}
}
