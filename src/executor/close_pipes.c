#include "minishell.h"

void	close_pipes_first(t_minivault *minivault)
{
    // Close the write end of the first pipe, as the parent won't write to it
    close(minivault->baobab->pipe_fd[0][WRITE]);
}

void	close_pipes_middle(t_minivault *minivault, int pos)
{
    // Close the write end of the previous pipe, as the parent won't write to it
    close(minivault->baobab->pipe_fd[pos - 1][WRITE]);

    // Close the read end of the current pipe, as the parent won't read from it
    close(minivault->baobab->pipe_fd[pos][WRITE]);
}

void	close_pipes_last(t_minivault *minivault)
{
    int last_pipe_index;

    last_pipe_index = count_tokens(PIPE, minivault->tokens) - 1;
    // Close the read end of the last pipe, as the parent won't read from it
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
