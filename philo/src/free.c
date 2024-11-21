/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:17:47 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/15 15:18:27 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_everything(t_input *input)
{
	long int	i;

	i = 0;
	while (i < input->nb_philo)
	{
		pthread_mutex_destroy(input->indiv[i].right_fork);
		pthread_mutex_destroy(&input->indiv[i].eat_lock);
		i++;
	}
	pthread_mutex_destroy(&input->dead_lock);
	pthread_mutex_destroy(&input->print_lock);
	free(input->indiv);
}
