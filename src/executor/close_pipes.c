#include "minishell.h"

void	close_pipes_first(t_minivault *minivault)
{
    close(minivault->baobab->pipe_fd[FIRST_ELEM][WRITE]);
}

void	close_pipes_middle(t_minivault *minivault, int pos)
{
    close(minivault->baobab->pipe_fd[pos - 1][WRITE]);
    close(minivault->baobab->pipe_fd[pos - 1][READ]);
    close(minivault->baobab->pipe_fd[pos][WRITE]);
}

void	close_pipes_last(t_minivault *minivault)
{
    int last_pipe_index;

    last_pipe_index = count_tokens(PIPE, minivault->tokens) - 1;
    close(minivault->baobab->pipe_fd[last_pipe_index][READ]);
}

void	close_pipes(t_minivault	*minivault, t_command *command, int pos)
{
    if (command->pos == FIRST)
        close_pipes_first(minivault);
    if (command->pos == MIDDLE)
        close_pipes_middle(minivault, pos);
    if (command->pos == LAST)
        close_pipes_last(minivault);
}
