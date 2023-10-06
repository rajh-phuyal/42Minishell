
#include "minishell.h"

// this function receives a string and what characters to look for
// and skip those characters and returns the addr of th first char
// after the skipped characters
char    *instrreplace(char *str, char *garbage)
{
    int     count;
    int     igarbage;

    count = 0;
    while (*str)
    {
        igarbage = 0;
        while (garbage[igarbage])
        {
            if (*str == garbage[igarbage])
            {
                count++;
            }
            igarbage++;
        }
    }
}

char    *strextract(char *str)
{
    char    *extracted;

    while (*str && (*str != ' ' || *str != '\t'))
        str++;
}