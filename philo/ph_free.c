/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:41:56 by lrafael           #+#    #+#             */
/*   Updated: 2024/11/06 11:43:47 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clean_up(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
        pthread_mutex_destroy(&data->fork_mutex[i]);
    pthread_mutex_destroy(&data->print_mutex);
    free(data->forks);
    free(data->philos);
    free(data->fork_mutex);
}
