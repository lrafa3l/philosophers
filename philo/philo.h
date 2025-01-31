/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrafael <lrafael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:05:17 by lrafael           #+#    #+#             */
/*   Updated: 2025/01/31 12:41:05 by lrafael          ###   ########.fr       */
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

typedef struct s_list
{
	int				id;
	int				died;
	int				eating;
	int				stopp;
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	stop;
	pthread_mutex_t	death;
	pthread_mutex_t	satisfied;
	pthread_mutex_t	print;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		times_each_philo_must_eat;
	long int		start_time;
	long int		last_meal;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

/* ph_init.c */
int					ft_init(int argc, char *argv[]);
t_list				*init_data(int argc, char *argv[], t_list *data);

/* ph_init_more.c */
t_list				*init(int argc, char *argv[], t_list *data);
t_list				*update_data(int argc, char *argv[], t_list *data);
void				pthreads_create(t_list *data);
void				pthreads_join(t_list *data);
void				pthreads_m_destroy(t_list *data);

/* ph_list.c */
t_list				*insert(t_list *data, int id, t_list *aux);
t_list *delete (t_list *data);

/* ph_utils.c */
int					check_args(int ac, char *av[]);
int					ft_strcmp(const char *s1, const char *s2);
long int			ft_atoi(const char *str);
long int			current_time(void);
t_list				*first_philo(t_list *data);

/* ph_routine.c */
void				*philo(void *arg);
void				*philos(void *arg);
t_list				*lock_mutexes(t_list *data);

/* ph_routine_utils.c */
int					ft_satisfied(t_list *data, t_list *aux, t_list *first);
int					ft_death(t_list *data);
int					ft_stop(t_list *data);
void				print_msg(t_list *data, char *str);
t_list				*print_s(t_list *data, char *str);

#endif