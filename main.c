#include <philosophers.h>

int	ft_philosophers(char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->all_ate = 0;
	data->died = 0;
	if (data->nb_philo < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->nb_philo > 250)
		return (1);
	if (av[5])
	{
		data->nb_eat = ft_atoi(av[5]);
		if (data->nb_eat <= 0)
			return (1);
	}
	else
		data->nb_eat = -1;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (ft_init_philo(data))
		return (2);
	return (0);
}

int	main(int ac, char **av)
{
	t_data *data;
	int		ret;
	
	data = NULL;
	data = malloc(sizeof(t_data));
	if (ac != 5 && ac != 6)
		return (write_error("Wrong amount of arguments"));
	if ((ret = ft_philosophers(av, data)))
		return (error_manager(ret));
	if (ft_init_threads(data))
		return (write_error("There was an error creating the threads"));
	return (0);
}
