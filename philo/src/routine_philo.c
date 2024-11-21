/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:21:41 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/21 15:39:40 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_simulation(t_input *input)
{
	int			i;
	pthread_t	check_dead;

	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_create(&input->indiv[i].thread, NULL, &complete_routine, \
			&input->indiv[i]) != 0)
			return (perror("pthread_create_indiv"), -1);
		i++;
	}
	if (pthread_create(&check_dead, NULL, &monitoring, input->indiv) != 0)
		return (perror("pthread_create_monitoring"), -1);
	if (pthread_join(check_dead, NULL) != 0)
		return (perror("pthread_join_monitoring"), -1);
	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_join(input->indiv[i].thread, NULL) != 0)
			return (perror("pthread_join_indiv"), -1);
		i++;
	}
	return (0);
}

void	print_eat_routine(t_philo *indiv)
{
	if (dead_philo(indiv) == -1)
		return ;
	pthread_mutex_lock(&indiv->eat_lock);
	print_output_message(indiv, indiv->philo_id, "is eating");
	indiv->time_stamp = get_current_time_ms();
	indiv->nb_times_eat += 1;
	pthread_mutex_unlock(&indiv->eat_lock);
	ft_usleep(indiv->input->time_eat, indiv->input);
}

void	eat_routine(t_philo *indiv)
{
	if (dead_philo(indiv) == -1)
		return ;
	if (indiv[0].input->nb_philo == 1 && solo_philo(indiv))
		return ;
	if (indiv->philo_id % 2 == 0)
		even_philo(indiv);
	else
		odd_philo(indiv);
	print_eat_routine(indiv);
	if (indiv->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(&indiv->left_fork);
		pthread_mutex_unlock(indiv->right_fork);
	}
	else
	{
		pthread_mutex_unlock(indiv->right_fork);
		pthread_mutex_unlock(&indiv->left_fork);
	}
}

void	sleep_think_routine(t_philo *indiv)
{
	if (dead_philo(indiv) != -1)
	{
		print_output_message(indiv, indiv->philo_id, "is sleeping");
		ft_usleep(indiv->input->time_sleep, indiv->input);
		print_output_message(indiv, indiv->philo_id, "is thinking");
	}
}

void	*complete_routine(void *arg)
{
	t_philo	*indiv;

	indiv = (t_philo *)arg;
	if (dead_philo(indiv) == -1)
		return (NULL);
	if (indiv->philo_id % 2 == 0)
		ft_usleep(100, indiv->input);
	while (1)
	{
		if (dead_philo(indiv) == -1)
			break ;
		eat_routine(indiv);
		if (dead_philo(indiv) == -1)
			break ;
		sleep_think_routine(indiv);
	}
	return (arg);
}
