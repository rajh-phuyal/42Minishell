#include "minishell.h"

void	_env(t_minivault *minivault, int out_fd)
{
	t_envs	*envs;

	envs = minivault->envs;
	while (envs)
	{
		if (envs->session && !envs->internal)
		{
			ft_putstr_fd(envs->key, out_fd);
			ft_putstr_fd("=", out_fd);
			ft_putstr_fd(envs->value, out_fd);
			ft_putstr_fd("\n", out_fd);
		}
		envs = envs->next;
	}
	set_env(minivault, PREVEXITSTAT, ft_itoa(SUCCESS), (1 << 1));
}
