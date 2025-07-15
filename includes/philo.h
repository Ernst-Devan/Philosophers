#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
#include <sys/select.h>
# include <unistd.h>
# include <stdbool.h>

enum e_state {
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_settings
{
	unsigned int	nb_philo;
	int				nb_eat;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
}	t_settings;

typedef struct s_fork
{
	pthread_mutex_t mutex;
	bool		state;
}	 t_fork;

typedef struct s_philo 
{
	unsigned int	id;
	enum e_state	state;
	t_fork			*r_fork;
	t_fork			*l_fork;

} t_philo;

# endif
