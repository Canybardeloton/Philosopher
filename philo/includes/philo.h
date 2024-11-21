/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:53:54 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/21 14:47:41 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				philo_id;
	int				dead;
	long			time_stamp;
	long int		nb_times_eat;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	struct s_input	*input;
}					t_philo;

typedef struct s_input
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meals_completed;
	int				nb_eat;
	int				dead_status;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	struct s_philo	*indiv;
}					t_input;

// ft_utils_init.c
int		ft_atol(const char *s);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	free_everything(t_input *input);

//ft_init_struct.c
int		check_input(char **av);
int		initiate_struct_input(t_input *input, char **av);
int		fill_struct_philo(t_input *input);
int		initiate_struct(t_input *input, char **av);

//ft_print_utils.c
void	print_struct(t_input *input);
void	print_output_message(t_philo *data, int indiv, char *status);
long	get_current_time_ms(void);
void	print_dead(t_philo *data, int indiv, char *status);
void	print_all_eat(t_philo *data);

//routine_philo.c
void	eat_routine(t_philo *indiv);
void	sleep_think_routine(t_philo *indiv);
void	*complete_routine(void *arg);
int		philo_simulation(t_input *input);

// ft_utils_routine.c
int		dead_philo(t_philo *indiv);
int		solo_philo(t_philo *indiv);
void	even_philo(t_philo *indiv);
void	odd_philo(t_philo *indiv);
void	ft_usleep(size_t ms, t_input *input);

//monitoring.c
int		dead_monitoring(t_philo *indiv, int i);
int		philo_died(t_philo *indiv);
void	*monitoring(void *arg);

#endif