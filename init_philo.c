/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clora-ro <clora-ro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:16:40 by clora-ro          #+#    #+#             */
/*   Updated: 2022/08/20 13:03:25 by clora-ro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	ft_init_fork(t_data *data)
{
	int	i;

	i = data->nb_philo;
	pthread_mutex_init(&data->philo[0].lfork, NULL);
	while (i-- > 0)
	{
		if (pthread_mutex_init(&data->philo[i].lfork, NULL))
			return (1);
		data->philo[i].rfork = &data->philo[(i + 1) % data->nb_philo].lfork;
	}
	if (data->nb_philo == 1)
		data->philo[0].rfork = NULL;
	return (0);
}

int	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	if (ft_init_fork(data) == 1)
		return (1);
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (1);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].x_ate = 0;
		data->philo[i].t_last_meal = 0;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}
