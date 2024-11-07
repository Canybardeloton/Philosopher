/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:00:12 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 14:46:37 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_output_message(t_input *input, int indiv, char *status)
{
	pthread_mutex_lock(&input->print_lock);
	printf("%ld philosopher_%d %s\n", get_current_time_ms(), indiv, status);
	pthread_mutex_unlock(&input->print_lock);
}

void	print_struct(t_input *input)
{
	printf("input->nb_philo : %d\n", input->nb_philo);
	printf("input->time_die : %d\n", input->time_die);
	printf("input->time_eat : %d\n", input->time_eat);
	printf("input->time_sleep : %d\n", input->time_sleep);
	printf("input->nb_eat : %d\n", input->nb_eat);
}
