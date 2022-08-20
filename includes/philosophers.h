/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clora-ro <clora-ro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:22:26 by clora-ro          #+#    #+#             */
/*   Updated: 2022/08/19 16:36:13 by clora-ro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include "../libft/libft.h"

typedef struct s_philo
{
	int	id;
	int	x_ate;
	long long	t_last_meal;

	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	pthread_t thread_philo;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int	nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int	nb_eat;
	int	all_ate;
	int	died;
	
	long long	start_time;
	
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
	
	t_philo *philo;
}	t_data;


/*									main.c									*/

int		ft_philosophers(char **av, t_data *data);


/*									init_philo.c									*/

int		ft_init_fork(t_data *data);
int		ft_init_philo(t_data *data);


/*									init_thread.c									*/

void	philo_eats(t_philo *philo);
void	ft_destroy(t_data *data);
int 	ft_init_threads(t_data *data);


/*									error.c									*/

int		write_error(char *str);
int		error_manager(int error);


/*									utils.c									*/

long long	get_time(void);
long long	time_diff(long long past, long long pres);
void	ft_usleep(long long time, t_data *data);
void    print_action(t_data *data, int id, char *str);


#endif
