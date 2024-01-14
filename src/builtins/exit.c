/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:58:52 by rajphuyal         #+#    #+#             */
/*   Updated: 2023/12/31 15:34:44 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_minivault *minivault, int status)
{
    liberation(minivault);
    exit(status);
}

static  bool _str_long_long(char *str, long long *result)
{
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			if (*result > (LLONG_MAX - (*str - '0')) / 10)
				return (false);
			*result = *result * 10 + (*str - '0');
		}
		else
			return (false);
		str++;
	}
	return (true);
}

static bool    _is_long_min(const char *str1, const char *str2)
{
    if (!str1 || !str2)
        return (false);
    if (ft_strlen(str1) == ft_strlen(str2))
    {
        if (!ft_strncmp(str1, str2, ft_strlen(str1)))
            return (true);
    }
    return (false);
}

static bool _validate_long_long(char *str, int *status)
{
	int			sign;
	long long	result;

    sign = 1;
	result = 0;
	if (*str == '\0')
		return (false);
	if (_is_long_min(str, "-9223372036854775808"))
	{
		*status = 0;
		return (true);
	}
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!_str_long_long(str, &result))
		return (false);
	if (result > 0 && sign == -1)
		result *= -1;
	*status = (int)(result % 256);
	return (true);
}

void    _exit_vault(t_minivault *minivault, t_word *args)
{
    int _status;

    ft_putstr_fd("exit\n", STDOUT_FILENO);
    if (!args || !(args->word))
        clean_exit(minivault, ft_atoi(get_env(minivault, "?")));
    else
    {
        if (_validate_long_long(args->word, &_status))
		{
			if (args && args->next)
                error(minivault, FAILURE, true, "exit: ", "too many arguments", NULL);
			else
                clean_exit(minivault, (_status % MAXEXTSTATUS));
		}
		else
        {
			error(minivault, EXTSTATUSNONNUM, true, "exit:", args->word, ": ", "numeric argument required", NULL);
            clean_exit(minivault, EXTSTATUSNONNUM);
        }
    }
}
