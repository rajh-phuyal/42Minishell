#include "minishell.h"

// add a panic attack that will kill all the process and exit minishell
// don't know what is the exact use case of panic mode
// if its to exit with a status, call the
// internal exit function _exit instead
// if just to clean the cycle, call cycle_reset
void	panic_attack(t_minivault *minivault)
{
	cycle_reset(minivault);
}

// using int instead of bool because va_start
// will have undefined behavior if used with bool
void	error(t_minivault *minivault, t_status status, int prompt, ...)
{
	va_list	args;
	char	*_string;

	va_start(args, prompt);
	_string = concat_all(args);
	va_end(args);
	if (_string)
	{
		if (!prompt)
			ft_putendl_fd(_string, STDERR_FILENO);
		else
		{
			ft_putstr_fd("minibaiters: ", STDERR_FILENO);
			ft_putendl_fd(_string, STDERR_FILENO);
		}
		free(_string);
	}
	if (status != REDIRFAIL)
		cycle_reset(minivault);
	set_env(minivault, "?", ft_itoa(status), (1 << 1));
}
