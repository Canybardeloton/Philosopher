/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:18:56 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/21 15:15:43 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	dead_philo(t_philo *indiv)
{
	if (indiv == NULL)
		return (-1);
	pthread_mutex_lock(&indiv->input->dead_lock);
	if (indiv[0].input->dead_status == 1)
	{
		pthread_mutex_unlock(&indiv->input->dead_lock);
		return (-1);
	}
	pthread_mutex_unlock(&indiv->input->dead_lock);
	return (0);
}

int	solo_philo(t_philo *indiv)
{
	pthread_mutex_lock(indiv->right_fork);
	print_output_message(indiv, indiv->philo_id, "has taken a fork");
	ft_usleep(indiv->input->time_die, indiv->input);
	pthread_mutex_unlock(indiv->right_fork);
	return (1);
}

void	odd_philo(t_philo *indiv)
{
	if (dead_philo(indiv) == -1)
		return ;
	pthread_mutex_lock(indiv->right_fork);
	print_output_message(indiv, indiv->philo_id, "has taken a fork");
	pthread_mutex_lock(&indiv->left_fork);
	print_output_message(indiv, indiv->philo_id, "has taken a fork");
}

void	even_philo(t_philo *indiv)
{
	if (dead_philo(indiv) == -1)
		return ;
	pthread_mutex_lock(&indiv->left_fork);
	print_output_message(indiv, indiv->philo_id, "has taken a fork");
	pthread_mutex_lock(indiv->right_fork);
	print_output_message(indiv, indiv->philo_id, "has taken a fork");
}

void	ft_usleep(size_t time_ms, t_input *input)
{
	size_t	start_time;

	start_time = get_current_time_ms();
	while ((get_current_time_ms() - start_time) < time_ms)
	{
		if (dead_philo(input->indiv) == -1)
			return ;
		usleep(500);
	}
}
