/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:43:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 14:31:59 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init(t_input **input)
{
	(*input) = malloc(sizeof(t_input));
	if (!(*input))
		return (-1);
	(*input)->nb_philo = 0;
	(*input)->time_die = 0;
	(*input)->time_eat = 0;
	(*input)->time_sleep = 0;
	(*input)->nb_eat = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_input	*input;

	input = NULL;
	if (ac == 6)
	{
		init(&input);
		if (initiate_struct(input, av) == -1)
			return (0);
		philo_simulation(input);
	}
	return (0);
}
