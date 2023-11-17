# include "minishell.h"

void    throw_error(t_minivault *minivault, char *error_message, char *arg, int status)
{
    // throught errors to the FD 2 (stderr)


    if (arg)
        printf("minibaiters: %s: %s\n", arg, error_message);
    elses
        printf("minibaiters: %s\n", error_message);
    liberation(minivault);
    exit(1);
}