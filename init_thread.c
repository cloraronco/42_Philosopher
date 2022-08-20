/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clora-ro <clora-ro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:43:56 by clora-ro          #+#    #+#             */
/*   Updated: 2022/08/20 12:47:59 by clora-ro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->lfork);
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->rfork);
	print_action(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&data->meal_check);
	print_action(data, philo->id, "is eating");
	philo->t_last_meal = get_time();
	pthread_mutex_unlock(&data->meal_check);
	ft_usleep(data->time_to_eat, data);
	(philo->x_ate)++;
	pthread_mutex_unlock(&philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

static void*	fn_philo(void *p_philo)
{
	int	i;
	t_philo	*philo = (t_philo *) p_philo;
	t_data	*data;

	i = 0;
	data = philo->data;
	if (philo->id % 2 != 0)
	{
		print_action(data, philo->id, "is thinking");
		usleep(15000);
	}
	while (!(data->died))
	{
		philo_eats(philo);
		if (data->all_ate)
			break;
		print_action(data, philo->id, "is sleeping");
		usleep(data->time_to_sleep * 1000);
		print_action(data, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread_philo, NULL);
		i++;
	}
	pthread_mutex_destroy(&(data->writing));
}

void	death_checker(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		while (++i < data->nb_philo && !(data->died))
		{
			pthread_mutex_lock(&(data->meal_check));
			if (time_diff(philo[i].t_last_meal, get_time()) > data->time_to_die)
			{
				print_action(data, i, "died");
				data->died = 1;
			}
			pthread_mutex_unlock(&(data->meal_check));
			usleep(100);
		}
		if (data->died)
			break;
		i = 0;
		while (data->nb_eat != -1 && i < data->nb_philo && philo[i].x_ate >= data->nb_eat)
			i++;
		if (i == data->nb_philo)
			data->all_ate = 1;
	}
}

int	ft_init_threads(t_data *data)
{
	int i = 0;
	t_philo	*philo;

	philo = data->philo;
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread_philo, NULL, fn_philo, (void *) &data->philo[i]))
			return (1);
		data->philo[i].t_last_meal = get_time();
		i++;
	}
	death_checker(data, philo);
	ft_destroy(data);
	return (0);
}
