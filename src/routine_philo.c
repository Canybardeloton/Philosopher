/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:21:41 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 14:54:27 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_simulation(t_input *input)
{
	int			i;
	pthread_t	*player;

	player = malloc(sizeof(pthread_t) * input->nb_philo);
	if (!player)
		return ;
	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_create(&player[i], NULL, &complete_routine, \
			&input->indiv[i]) != 0)
		{
			free(player);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_join(player[i], NULL) != 0)
			return ;
		i++;
	}
	free(player);
}

void	*complete_routine(void *arg)
{
	t_philo	*indiv;
	t_input	*input;

	indiv = (t_philo *)arg;
	input = indiv->input;
	while (1)
	{
		print_output_message(input, indiv->philo_id, "is thinking");
		pthread_mutex_lock(indiv->left_fork);
		print_output_message(input, indiv->philo_id, "has taken a fork");
		pthread_mutex_lock(indiv->right_fork);
		print_output_message(input, indiv->philo_id, "has taken a fork");
		usleep(10);
		indiv->time_stamp = get_current_time_ms();
		print_output_message(input, indiv->philo_id, "is eating");
		if (usleep(input->time_eat * 1000) == input->time_die * 1000)
			break ;
		pthread_mutex_unlock(indiv->left_fork);
		pthread_mutex_unlock(indiv->right_fork);
		print_output_message(input, indiv->philo_id, "is sleeping");
		if (usleep(input->time_sleep * 1000) == input->time_die * 1000)
			break ;
	}
	return (NULL);
}
