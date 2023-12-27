# include "minishell.h"


// add a panic attack that will kill all the process and exit minishell
void    panic_attack(t_minivault *minivault)
{
	// don't know what is the exact use case of panic mode
	// if its to exit with a status, call the internal exit function _exit instead
	// if just to clean the cycle, call cycle_reset
	cycle_reset(minivault);
	// exit(FAILURE);
}

static	char    *concat_all(va_list args)
{
    char	*iter;
	char	*temp;
    char	*_string;

	temp = NULL;
	_string = va_arg(args, char *);
    if (!_string)
        return (temp);
	_string = ft_strdup(_string);
	iter = va_arg(args, char *);
    while (iter)
	{
		temp = ft_strjoin(_string, iter);
        free(_string);
        _string = temp;
        if (!_string)
            return (NULL);
		iter = va_arg(args, char *);
    }
    return (_string);
}

// using int instead of bool because va_start will have undefined behavior if used with bool
void    error(t_minivault *minivault, t_status status, int prompt, ...)
{
    va_list args;
	char 	*_string;

    va_start(args, prompt);
    _string = concat_all(args);
    va_end(args);
	if (_string)
	{
		if (!prompt)
			printf("%s\n", _string);
		else
			printf("minibaiters: %s\n", _string);
    	free(_string);
	}
    cycle_reset(minivault);
    set_env(minivault, "?", ft_itoa(status), (1 << 1));
}
