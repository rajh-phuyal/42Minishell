#include "minishell.h"

int	get_envlen(t_envs *envs)
{
	int	len;

	len = 0;
	while (envs)
	{
		len++;
		envs = envs->next;
	}
	return (len);
}

void	transfer_data(t_envs *envs, char **data)
{
	while (envs)
	{
		*data = envs->key;
		envs = envs->next;
		data++;
	}
}

int	partition(char **data, int start, int end)
{
	int		i;
	int		j;
	char	*pivot;
	char	*temp;

	pivot = data[end];
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (ft_strncmp(data[j], pivot, ft_strlen(data[j])) < 0)
		{
			i++;
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
		j++;
	}
	temp = data[i + 1];
	data[i + 1] = data[end];
	data[end] = temp;
	return (i + 1);
}

void	quicksort(char **data, int start, int end)
{
	int	pivot;

	if (start < end)
	{
		pivot = partition(data, start, end);
		quicksort(data, start, pivot - 1);
		quicksort(data, pivot + 1, end);
	}
}

char	**envsort(t_envs *envs)
{
	int		len;
	char	**data;

	len = get_envlen(envs);
	data = (char **)malloc(sizeof(char *) * (len + 1));
	data[len] = NULL;
	transfer_data(envs, data);
	quicksort(data, 0, len - 1);
	return (data);
}
