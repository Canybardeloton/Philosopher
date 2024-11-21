/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:51:04 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/21 15:43:23 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	dead_monitoring(t_philo *indiv, int i)
{
	if (dead_philo(indiv) == -1)
		return (-1);
	pthread_mutex_lock(&indiv[i].eat_lock);
	if (get_current_time_ms() - indiv[i].time_stamp >= indiv->input->time_die)
		return (pthread_mutex_unlock(&indiv->eat_lock), -1);
	pthread_mutex_unlock(&indiv[i].eat_lock);
	return (0);
}

int	philo_died(t_philo *indiv)
{
	int	i;

	i = 0;
	while (i < indiv->input->nb_philo)
	{
		if (dead_monitoring(&indiv[i], i) == -1)
		{
			pthread_mutex_lock(&indiv[0].input->dead_lock);
			indiv[0].input->dead_status = 1;
			pthread_mutex_unlock(&indiv[0].input->dead_lock);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	eat_reached(t_philo *indiv)
{
	int	complete_meals;
	int	i;

	complete_meals = 0;
	i = 0;
	if (indiv->input->nb_eat == -1)
		return (0);
	while (i < indiv->input->nb_philo)
	{
		pthread_mutex_lock(&indiv[i].eat_lock);
		if (indiv[i].nb_times_eat >= indiv->input->nb_eat)
			complete_meals++;
		pthread_mutex_unlock(&indiv[i].eat_lock);
		i++;
	}
	if (complete_meals >= indiv->input->nb_philo)
	{
		pthread_mutex_lock(&indiv[0].input->dead_lock);
		indiv[0].input->dead_status = 1;
		pthread_mutex_unlock(&indiv[0].input->dead_lock);
		return (-1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*indiv;

	indiv = (t_philo *)arg;
	if (philo_died(indiv) == -1)
		return (NULL);
	while (1)
	{
		if (eat_reached(indiv) == -1)
		{
			print_all_eat(indiv);
			break ;
		}
		if (philo_died(indiv) == -1)
		{
			print_dead(indiv, indiv->philo_id, "died");
			break ;
		}
		ft_usleep(100, indiv->input);
	}
	return (NULL);
}
