# include "minishell.h"


// add a panic attack that will kill all the process and exit minishell
void    panic_mode(void)
{
    return ;
}

void    error(t_minivault *minivault, t_status status, char *message, char *token)
{
    minivault->error->status = status;
    minivault->error->message = message;
    minivault->error->err_token = token;
    // TODO: handel command not found, file not found etc
    printf("minibaiters: %s: %s", message, token);
}
