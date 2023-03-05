#include "pipex.h"

char *free_s(char **addr)
{
    free(*addr);
    *addr = 0x0;
    return (NULL);
}

char *free_d(char ***addr)
{
    size_t i;

    i = 0;
    if(!(*addr))
    {
        while(*addr[i])
            free_s(&(*addr[i]));
        free(*addr);
        *addr = 0;
    }
    return (NULL);
}