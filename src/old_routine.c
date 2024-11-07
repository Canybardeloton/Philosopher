int	routine_eat(t_input *philo, t_philo *indiv)
{
	int	eat;
	int	total;
	int	die;

	total = philo->time_eat * 1000 + philo->time_sleep * 1000;
	eat = philo->time_eat * 1000;
	die = philo->time_die * 1000;
	if (total > die)
		return (-1);
	while (eat > 0 && total > die)
	{
		indiv->state = 2;
		print_output_message(indiv);
		eat--;
		total--;
	}
	if (eat != 0)
	{
		indiv->state = 5;
		print_output_message(indiv);
		return (-1);
	}
	return (total);
}

int	routine_sleep(t_input *philo, int total, t_philo *indiv)
{
	int	sleep;
	int	die;

	die = philo->time_die * 1000;
	sleep = philo->time_sleep * 1000;
	while (sleep > 0 && total > die)
	{
		indiv->state = 3;
		print_output_message(indiv);
		sleep--;
		total--;
	}
	if (sleep != 0)
	{
		indiv->state = 5;
		print_output_message(indiv);
		return (-1);
	}
	return (total);
}

int	routine_think(t_input *philo, int total, t_philo *indiv)
{
	int	think;
	int	die;

	die = philo->time_die * 1000;
	think = philo->time_think * 1000;
	while (think > 0 && total > die)
	{
		indiv->state = 4;
		print_output_message(indiv);
		think--;
		total--;
	}
	if (think != 0)
	{
		indiv->state = 5;
		print_output_message(indiv);
		return (-1);
	}
	return (total);
}

int	routine_philo(t_input *philo, t_philo *indiv)
{
	int	total;

	indiv->state = 1;
	if (indiv->fork != 2)
		return (-1);
	print_output_message(indiv);
	total = routine_eat(philo, indiv);
	if (total == -1)
		return (-1);
	if (routine_sleep(philo, total, indiv) == -1)
		return (-1);
	if (routine_think(philo, total, indiv) == -1)
		return (-1);
	return (0);
}

int	fill_struct_philo(t_philo **philo, t_input **input)
{
	int		i;
	t_philo	*node;

	i = 1;
	while (i < (*input)->nb_philo)
	{
		node = ft_new_philo(philo, i);
		if (!node)
		{
			ft_lstclear_philo(philo, del);
			return (-1);
		}
		if ((*philo) != NULL)
			ft_lstadd_back_philo(philo, node);
		i++;
	}
	(*input)->indiv = *philo;
	return (0);
}