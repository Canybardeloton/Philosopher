/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:53:54 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 14:41:42 by agiliber         ###   ########.fr       */
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

typedef struct s_philo
{
	int				philo_id;
	int				state;
	long			time_stamp;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_input	*input;
}					t_philo;

typedef struct s_input
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	struct s_philo	*indiv;
}					t_input;

// ft_utils_init.c
t_philo	*ft_new_philo(t_philo **philo, int content);
void	del(int content);
int		ft_atoi(const char *s);
void	ft_lstclear_philo(t_philo **lst, void (*del)(int));
void	ft_lstadd_back_philo(t_philo **lst, t_philo *new);

//ft_init_struct.c
int		initiate_struct_input(t_input *input, char **av);
int		fill_struct_philo(t_input *input);
int		initiate_struct(t_input *input, char **av);

//ft_print_utils.c
void	print_struct(t_input *input);
void	print_output_message(t_input *input, int indiv, char *status);
long	get_current_time_ms(void);

//routine_philo.c
int		routine_eat(t_input *philo, t_philo *indiv);
int		routine_sleep(t_input *philo, int total, t_philo *indiv);
int		routine_think(t_input *philo, int total, t_philo *indiv);
int		routine_philo(t_input *philo, t_philo *indiv);
void	*complete_routine(void *arg);
void	philo_simulation(t_input *input);

#endif