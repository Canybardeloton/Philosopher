/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:48:18 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 14:43:33 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	initiate_struct(t_input *input, char **av)
{
	if (initiate_struct_input(input, av) == -1)
		return (-1);
	if (fill_struct_philo(input) == -1)
		return (-1);
	return (0);
}

int	fill_struct_philo(t_input *input)
{
	int	i;

	i = 0;
	input->forks = malloc(sizeof(pthread_mutex_t) * \
		input->nb_philo);
	if (!input->forks)
		return (-1);
	input->indiv = malloc(sizeof(t_philo) * input->nb_philo);
	if (!input->indiv)
		return (free(input->forks), -1);
	while (i < input->nb_philo)
	{
		input->indiv[i].philo_id = i + 1;
		input->indiv[i].state = 0;
		input->indiv[i].time_stamp = get_current_time_ms();
		input->indiv[i].left_fork = &input->forks[i];
		input->indiv[i].right_fork = &input->forks[(i + 1) % input->nb_philo];
		input->indiv[i].input = input;
		i++;
	}

	pthread_mutex_init(&input->print_lock, NULL);
	return (0);
}

int	initiate_struct_input(t_input *input, char **av)
{
	input->nb_philo = ft_atoi(av[1]);
	if (input->nb_philo < 1)
		return (-1);
	input->time_die = ft_atoi(av[2]);
	if (input->time_die < 1)
		return (-1);
	input->time_eat = ft_atoi(av[3]);
	if (input->time_eat < 1)
		return (-1);
	input->time_sleep = ft_atoi(av[4]);
	if (input->time_sleep < 1)
		return (-1);
	input->nb_eat = ft_atoi(av[5]);
	if (input->nb_eat < 0)
		return (-1);
	return (0);
}
