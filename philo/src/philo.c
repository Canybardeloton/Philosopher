/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:43:59 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/18 13:18:16 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_input	input;

	if (ac == 5 || ac == 6)
	{
		if (initiate_struct(&input, av) == -1)
			return (write(2, "Invalid arguments\n", 19), 0);
		if (philo_simulation(&input) == -1)
			return (0);
		free_everything(&input);
	}
	return (0);
}
