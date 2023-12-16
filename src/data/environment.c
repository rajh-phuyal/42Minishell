
#include "minishell.h"

void    add_env_node(t_minivault *minivault, char *key, char *value, int identifier)
{
	t_envs	*new;
    t_envs	*envs;

	new = (t_envs *)malloc(sizeof(t_envs));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
    new->internal = (identifier >> 1) & 1;
    new->session = (identifier >> 2) & 1;
	new->next = NULL;
	if (!minivault->envs)
    {
        minivault->envs = new;
        return ;
    }
    envs = minivault->envs;
	while (envs->next)
		envs = envs->next;
	envs->next = new;
}

char	*get_env(t_minivault *minivault, char *key)
{
	t_envs	*envs;

	envs = minivault->envs;
	while (envs)
	{
		if (!ft_strncmp(envs->key, key, ft_strlen(key)))
			return (envs->value);
		envs = envs->next;
	}
    return (NULL);
}

t_envs  *get_env_node(t_minivault *minivault, char *key)
{
	t_envs	*envs;

	envs = minivault->envs;
	while (envs)
	{
		if (!ft_strncmp(envs->key, key, ft_strlen(key)))
			return (envs);
		envs = envs->next;
	}
    return (NULL);
}

void	set_env(t_minivault *minivault, char *key, char *value, int identifier)
{
    t_envs	*envs;

    envs = minivault->envs;
    while (envs)
    {
        if (!ft_strncmp(envs->key, key, ft_strlen(envs->key)))
        {
            free(envs->value);
            envs->value = value;
            return ;
        }
        envs = envs->next;
    }
    add_env_node(minivault, key, value, identifier);
}

void    unset_env(t_minivault *minivault, char *key) // WIP
{
    t_envs	*envs;
    t_envs	*temp;

    temp = NULL;
    envs = minivault->envs;
    while (envs)
    {
        if (!ft_strncmp(envs->key, key, ft_strlen(key)))
        {
            free(envs->value);
            free(envs->key);
            if (temp)
                temp->next = envs->next;
            if (envs == minivault->envs)
                minivault->envs = envs->next;
            free(envs);
            break ;
        }
        temp = envs;
        envs = envs->next;
    }
}