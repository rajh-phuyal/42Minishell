
#include "minishell.h"

// this function receives a string and what characters to look for
// and skip those characters and returns the addr of th first char
// after the skipped characters
char    *strskip(char *str, char *garbage)
{
    while (str && *str && ft_strchr(garbage, *str))
        str++;
    return (str);
}

void    strcompact(char **str)
{
    char    *compact;

    ft_printf("STR in compact: %s\n", *str);
    compact = malloc(sizeof(char) * (ft_strlen(*str) + 1));
    if (!compact)
        return ;
    while (*str)
        *compact++ = *(*str)++;
    *compact = '\0';
    free(*str);
    *str = compact;
}

// this function receives a string and seperates them with a special seperator
char    *strmodify(char *str)
{
    char    *prev;
    char    *modified;

    modified = malloc(sizeof(char) * (ft_strlen(str) * 2));
    if (!modified)
        return (NULL);
    prev = str;
    str = strskip(str, " \t");
    while (str && *str)
    {
        str = strskip(str, " \t");
        if (prev == (str - 1))
        {
            ft_printf("in if\n");
            *modified++ = *str;
            if (*modified == '|')
                *modified++ = ' ';
        }
        else
        {
            str++;
            *modified++ = ' ';
            ft_printf("in else\n");
            // printf("MODIFIED: %s\n", modified);
        }
    }
    *modified = '\0';
    printf("MODIFIED: %s\n", modified);
    strcompact(&modified); // modified still have some memory after the \0
    return (modified);
}

// prints the splitted string with index
void    print_split(char **split)
{
    int     i;

    i = 0;
    while (split[i])
    {
        printf("%d: %s\n", i, split[i]);
        i++;
    }
}

void    strextract(t_minivault *minivault, char *input)
{
    input = strmodify(input);
    minivault->input = ft_split(input, ' '); // later do a better version of the split
    printf("SPLITED:\n");
    print_split(minivault->input);
}