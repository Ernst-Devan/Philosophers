/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:40:47 by dernst            #+#    #+#             */
/*   Updated: 2025/08/07 14:49:09 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/select.h>
# include <unistd.h>
# include <stdbool.h>

// DEFINES

# define DEFAULT 200
# define DELAY 20000
# define DEAD 1

// STRUCTS

enum e_state
{
	EAT,
	FORK,
	SLEEP,
	THINK,
	ALIVE,
	DIE
};

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			state;
}	t_fork;

typedef struct s_data
{
	unsigned int		nb_philo;
	unsigned int		nb_eat;
	unsigned int		time_eat;
	unsigned int		time_sleep;
	unsigned int		time_die;
	unsigned long		time_start;
	pthread_mutex_t		mutex_printf;
	pthread_mutex_t		mutex_state;
	bool				state;
	pthread_mutex_t		mutex_die;
	bool				philo_die;
	pthread_mutex_t		mutex_eat;
	unsigned int		all_eat;
}	t_data;

typedef struct s_philo
{
	unsigned int	id;
	unsigned long	last_meal;
	t_fork			*r_fork;
	t_fork			*l_fork;
	t_data			*data;
	unsigned int	nb_eat;
}	t_philo;

// Death.c
bool			check_death(t_philo *philo, unsigned long time_start);
unsigned int	kill_philo(t_philo *philo, unsigned long time_start);
bool			check_philo_die(t_data *data);
unsigned int	death_print(t_philo *philo, unsigned long time_start);

// Time.c
unsigned long	get_time(void);
unsigned long	current_time(unsigned long time_start);
bool			ft_usleep(t_philo *philo, unsigned long sleep,
					unsigned long start);

// Debug.c
void			display_data(t_data data);
void			display_philo(t_philo *philo, unsigned int nb_philo);

// Init.c
void			init_data(t_data *data, char **argv, int argc);
int				invite_philosophers(t_data *data, t_philo **philo);
int				set_table(unsigned int nb_philo, t_fork **fork);

// Fork.c
void			release_forks(t_philo *philo);
unsigned int	assign_fork(t_data *data, t_philo *philo, t_fork *forks);
int				lock_fork(t_philo *philo);
int				unlock_fork(t_philo *philo);
bool			fork_available(t_philo *philo, unsigned long time_start);

// Thread.c
int				launch_dinner(t_data *data, t_philo *philo);
int				waiting_threads(t_data *data, pthread_t *threads);
int				launch_threads(t_philo *philo, pthread_t *threads);

// Utils.c
int				ft_atoi(char *str);

// Start.c
int				check_ready(t_data *data);
void			set_ready(t_data *data);

// Routine.c
void			*routine(void *thread);
int				go_sleep(t_philo *philo, unsigned long time_start);
int				go_think(t_philo *philo, unsigned long time_start);
int				go_eat(t_philo *philo, unsigned long time_start);

// Check.c
unsigned int	check_args(char **argv, int argc);

// Print.c
unsigned int	print(t_philo *philo, enum e_state state, unsigned long time);

#endif
