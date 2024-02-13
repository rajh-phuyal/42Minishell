#include "minishell.h"

char	*concat_all(va_list args)
{
	char	*iter;
	char	*temp;
	char	*_string;

	temp = NULL;
	_string = va_arg(args, char *);
	if (!_string)
	{
		return (temp);
	}
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

void	_free_or_not_free(bool exist, char **vec)
{
	int	i;

	i = 0;
	while (vec && vec[i])
	{
		if (i == 0 && exist)
			free(vec[i]);
		if (i >= 2)
			free(vec[i]);
		i++;
	}
	free(vec);
}

void	add_env_key_val(t_minivault *minivault, char **iter, bool exist)
{
	if (iter[FIRST_ELEM] && iter[SECOND_ELEM])
		set_env(minivault, iter[FIRST_ELEM], \
				iter[SECOND_ELEM], (1 << 2));
	else if (iter[FIRST_ELEM])
		set_env(minivault, iter[FIRST_ELEM], \
				ft_strdup("\31"), (1 << 2));
	_free_or_not_free(exist, iter);
}