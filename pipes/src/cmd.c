#include "../include/pipes.h"

void	find_cmd1(void)
{
	char **cmd = ft_split(data()->cmd1, ' ');
	char *temp;
	int i = 0;

	while (data()->path[i])
	{
		temp = ft_strjoin(data()->path[i], "/");
		temp = ft_strjoin(temp, cmd[0]);
		if (access(temp, F_OK) == 0)
		{
			data()->cmd1_path = temp;
			return ;
		}
		free(temp);
		i++;
	}
}

void	find_cmd2(void)
{
	char **cmd = ft_split(data()->cmd2, ' ');
	char *temp;
	int i = 0;

	while (data()->path[i])
	{
		temp = ft_strjoin(data()->path[i], "/");
		temp = ft_strjoin(temp, cmd[0]);
		if (access(temp, F_OK) == 0)
		{
			data()->cmd2_path = temp;
			return ;
		}
		free(temp);
		i++;
	}
}