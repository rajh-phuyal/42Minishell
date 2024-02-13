#include "minishell.h"

void	_pwd(t_minivault *minivault, int out_fd)
{
	char	buffer[PATH_MAX];

	(void)minivault;
	if (!getcwd(buffer, sizeof(buffer)))
		set_env(minivault, PREVEXITSTAT, ft_itoa(FAILURE), (1 << 1));
	else
		set_env(minivault, "?", ft_itoa(SUCCESS), (1 << 1));
	ft_putendl_fd(buffer, out_fd);
	return ;
}
