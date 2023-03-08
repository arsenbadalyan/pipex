#include "pipex.h"

char *ft_realloc(char **str1, char **str2)
{
    char *result;

    if(!*str1)
        *str1 = ft_strdup("");
    if(!*str2)
        *str2 = ft_strdup("");
    result = ft_strjoin(*str1, *str2);
    free_s(str1);
    // free_s(str2);
    return (result);
}