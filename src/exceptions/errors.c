# include "minishell.h"

// bash: syntax error near unexpected token `newline'
// bash: syntax error near unexpected token `|'
// bash: file: No such file or directory
// command not found
void    display_error(t_minivault *minivault)
{
    if (minivault->error->fd > STDERR_FILENO)
        dup2(minivault->error->fd, 2);
}


// grabs all the varidic arguments,
// which are send in the data types of the t_error struct
// the first being, minivault
void    error(t_minivault *minivault, ...)
{
    va_list args;
    int     count;

    va_start(args, minivault);
    minivault->error->status = va_arg(args, t_error_type);
    minivault->error->message = va_arg(args, bool);
    minivault->error->status = va_arg(args, int);
    minivault->error->message = va_arg(args, char *);
    minivault->error->err_token = va_arg(args, char *);
    va_end(args);
    display_error(minivault);
}
