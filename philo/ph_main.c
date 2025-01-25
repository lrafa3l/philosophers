/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:01:11 by lrafael           #+#    #+#             */
/*   Updated: 2025/01/24 12:13:51 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("./philo n_philos time_to_die time_to_eat ");
		printf("time_to_sleep times_each_philosopher_must_eat\n");
		return (0);
	}
	ft_init(argc, argv);
	return (0);
}
