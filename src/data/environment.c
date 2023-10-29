
#include "minishell.h"

t_envs	*add_env_node(t_envs *envs, char *key, char *value)
{
	t_envs	*new;
	t_envs	*head;

	head = envs;
	new = (t_envs *)malloc(sizeof(t_envs));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!envs)
		return (new);
	while (envs->next)
		envs = envs->next;
	envs->next = new;
	return (head);
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

void	set_env(t_minivault *minivault, char *key, char *value)
{
    t_envs	*envs;

    envs = minivault->envs;
    while (envs)
    {
        if (!ft_strncmp(envs->key, key, ft_strlen(key)))
        {
            free(envs->value);
            envs->value = NULL;
            break ;
        }
        envs = envs->next;
    }
    if (!envs || !envs->value)
        minivault->envs = add_env_node(minivault->envs, key, value);\
    else
        envs->value = value;
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