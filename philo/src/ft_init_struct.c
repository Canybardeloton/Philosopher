/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:48:18 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/21 14:47:42 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (ft_atol(av[i]) < 0)
			return (-1);
		if (ft_strlen(av[i]) > 10)
			return (-1);
		if (ft_atol(av[i]) > INT_MAX)
			return (-1);
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	initiate_struct(t_input *input, char **av)
{
	if (check_input(av) == -1)
		return (-1);
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
	while (i < input->nb_philo)
	{
		input->indiv[i].philo_id = i + 1;
		input->indiv[i].time_stamp = get_current_time_ms();
		input->indiv[i].dead = 0;
		input->indiv[i].nb_times_eat = 0;
		if (i == input->nb_philo - 1)
			input->indiv[i].right_fork = &input->indiv[0].left_fork;
		else
			input->indiv[i].right_fork = &input->indiv[i + 1].left_fork;
		pthread_mutex_init(&input->indiv[i].left_fork, NULL);
		pthread_mutex_init(&input->indiv[i].eat_lock, NULL);
		input->indiv[i].input = input;
		input->indiv[i].start_time = get_current_time_ms();
		i++;
	}
	pthread_mutex_init(&input->dead_lock, NULL);
	pthread_mutex_init(&input->print_lock, NULL);
	return (0);
}

int	initiate_struct_input(t_input *input, char **av)
{
	input->nb_philo = ft_atol(av[1]);
	if (input->nb_philo == 0)
		return (-1);
	input->indiv = malloc(sizeof(t_philo) * input->nb_philo);
	if (!input->indiv)
		return (-1);
	input->time_die = ft_atol(av[2]);
	input->time_eat = ft_atol(av[3]);
	input->time_sleep = ft_atol(av[4]);
	input->dead_status = 0;
	input->meals_completed = 0;
	if (av[5] != NULL)
		input->nb_eat = ft_atol(av[5]);
	else
		input->nb_eat = -1;
	return (0);
}
