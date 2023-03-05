#include "pipex.h"

char *concat_file_name(char *command, char *file_name)
{
    char *temp;
    char *full;
    char *space;
    temp = ft_strjoin("< ", file_name);
    space = ft_strjoin(temp, " ");
    if(!temp)
        return (NULL);
    full = ft_strjoin(command, space);
    if(!full)
        return (free_s(&temp));
    return (full);
}

void execute_pipe(int argc, char **argv, char **envp, char **paths)
{
    size_t index;
    char *path;
    char **splited_cmd;
    char *concated;

    index = 2;
    while(index < (argc - 1))
    {
        path = is_command_executable(argv[index], paths);
        if(path)
        {
            splited_cmd = ft_split(concat_file_name(argv[index], argv[1]), ' ');
            if(execve(path, splited_cmd, NULL) != -1)
            {
                puts("WORKS");
            }
        }
        index++;
    }
}