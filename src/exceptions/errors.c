# include "minishell.h"


// add a panic attack that will kill all the process and exit minishell
void    panic_mode(void)
{
    return ;
}

// make a clean exit in the child process
void    error(t_minivault *minivault, t_status status, char *message, char *token)
{
    minivault->error->status = status;
    minivault->error->message = message;
    minivault->error->err_token = token;
    // TODO: handel command not found, file not found etc
    printf("minibaiters: %s: %s", message, token);
    set_env(minivault, "?", ft_itoa(status), (1 << 1));
}
