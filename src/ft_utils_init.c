/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:06:56 by agiliber          #+#    #+#             */
/*   Updated: 2024/11/07 11:54:22 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	test;

	i = 0;
	sign = 1;
	test = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		test = test * 10 + s[i] - '0';
		i++;
	}
	if (test > 2147483647 || test * -1 < -2147483648)
		return (0);
	return (test * sign);
}
/*
t_philo	*ft_new_philo(t_philo **philo, int content)
{
	t_philo	*tab;

	if (philo == NULL)
		return (NULL);
	tab = malloc(sizeof(t_philo));
	if (!tab)
		return (NULL);
	tab->philo_id = content;
	tab->time_stamp = 0;
	tab->right_fork = NULL;
	tab->left_fork = NULL;
	return (tab);
}

void	ft_lstadd_back_philo(t_philo **lst, t_philo *new)
{
	t_philo	*current;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while ((current)->right_fork != NULL)
		(current) = (current)->right_fork;
	(current)->right_fork = new;
	new->left_fork = current;
}

void	del(int content)
{
	(void) content;
}

void	ft_lstclear_philo(t_philo **lst, void (*del)(int))
{
	t_philo	*tab;
	t_philo	*next;

	if (!lst || !del || !*lst)
		return ;
	tab = *lst;
	while (tab != NULL)
	{
		next = tab->right_fork;
		((*del)(tab->philo_id));
		((*del)(tab->state));
		((*del)(tab->time_stamp));
		free((void *)tab);
		tab = next;
	}
	*lst = NULL;
}
 */