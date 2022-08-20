/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clora-ro <clora-ro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:41:29 by clora-ro          #+#    #+#             */
/*   Updated: 2022/08/18 10:41:29 by clora-ro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long long	get_time(void)
{
	struct timeval	time;
	long			milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000;
	milliseconds += time.tv_usec / 1000;
	return (milliseconds);
}

long long	time_diff(long long past, long long pres)
{
    return (pres - past);
}

void	ft_usleep(long long time, t_data *data)
{
	long long	i;

	i = get_time();
	while (!(data->died))
	{
        if (time_diff(i, get_time()) >= time)
            break ;
        usleep(50);
	}
	
}

void    print_action(t_data *data, int id, char *str)
{
    pthread_mutex_lock(&(data->writing));
    if (!(data->died))
    {
        printf("%lli ", get_time() - data->start_time);
        printf("%i ", id);
        printf("%s\n", str);
    }
    pthread_mutex_unlock(&(data->writing));
    return ;
}