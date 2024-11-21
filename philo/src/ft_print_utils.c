/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:00:12 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/21 14:47:43 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_output_message(t_philo *data, int indiv, char *status)
{
	long	time;

	if (dead_philo(data) == -1)
		return ;
	pthread_mutex_lock(&data->input->print_lock);
	time = get_current_time_ms() - data->start_time;
	printf("%ld %d %s\n", time, indiv, status);
	pthread_mutex_unlock(&data->input->print_lock);
}

void	print_struct(t_input *input)
{
	printf("input->nb_philo : %d\n", input->nb_philo);
	printf("input->time_die : %d\n", input->time_die);
	printf("input->time_eat : %d\n", input->time_eat);
	printf("input->time_sleep : %d\n", input->time_sleep);
	printf("input->nb_eat : %d\n", input->nb_eat);
}

void	print_dead(t_philo *data, int indiv, char *status)
{
	long	time;

	pthread_mutex_lock(&data->input->print_lock);
	time = get_current_time_ms() - data->start_time;
	printf("%ld %d %s\n", time, indiv, status);
	pthread_mutex_unlock(&data->input->print_lock);
}

void	print_all_eat(t_philo *data)
{
	long	time;

	pthread_mutex_lock(&data->input->print_lock);
	time = get_current_time_ms() - data->start_time;
	printf("%ld %s\n", time, "All meals completed. Stopping simulation");
	pthread_mutex_unlock(&data->input->print_lock);
}
