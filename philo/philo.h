/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:05:17 by lrafael           #+#    #+#             */
/*   Updated: 2024/11/07 08:02:44 by lrafael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				*forks;
	int				stop_simulation;
	t_philo			*philos;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	struct timeval	start_time;
}					t_data;

// typedef struct s_philo
// {
// 	int				id;
// 	long int		time_to_die;
// 	long int		time_to_eat;
// 	long int		time_to_sleep;
// 	long int		times_each_philo_must_eat;
// 	long int		start_time;
// 	long int		last_meal;
// 	int				time_stop;
// 	int				eating;
// 	int				died;
// }					t_philo;

// typedef struct s_data
// {
// 	pthread_mutex_t	fork;
// 	pthread_mutex_t	to_ms;
// 	pthread_mutex_t	to_sd;
// 	pthread_mutex_t	to_ea;
// 	pthread_mutex_t	to_ps;
// 	pthread_t		philo;
// 	struct s_philo	*prev;
// 	struct s_philo	*next;
// }					t_data;

int					ft_atoi(const char *str);
int					init_data(t_data *data, int argc, char *argv[]);

void				*philo_life(void *arg);
void				clean_up(t_data *data);

#endif