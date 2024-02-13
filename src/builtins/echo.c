#include "minishell.h"

static bool	_existance(bool exist, bool get)
{
	static bool	_exist = false;

	if (get)
		return (_exist);
	_exist = exist;
	return (exist);
}

static t_word	*_skip_options(t_word *args)
{
	while (args)
	{
		if (ft_strncmp(args->word, "-n", ft_strlen(args->word)) != 0)
			return (args);
		_existance(true, false);
		args = args->next;
	}
	return (args);
}

void	_echo(t_minivault *minivault, t_word *args, int out_fd)
{
	_existance(false, false);
	if (args)
	{
		args = _skip_options(args);
		while (args)
		{
			ft_putstr_fd(args->word, out_fd);
			if (args->next)
				ft_putchar_fd(' ', out_fd);
			args = args->next;
		}
		if (!_existance(false, true))
			ft_putchar_fd('\n', out_fd);
	}
	else
		ft_putchar_fd('\n', out_fd);
	set_env(minivault, PREVEXITSTAT, ft_itoa(SUCCESS), (1 << 1));
}
