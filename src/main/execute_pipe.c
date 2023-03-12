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
	char **command_arr;

	index = 1;
	while(index < argc)
	{
		command_arr = ft_split(argv[index], ' ');
			path = is_command_executable(command_arr[0], paths);
		if(!path)
			write_exception(404);
		if(index == (argc - 1))
			pipe_commands(argv, path, command_arr);
		else
			execve(path, command_arr, NULL);
		index++;
	}
}

void pipe_commands(char **argv, char *path, char **command)
{
	int pid;
	int fd[2];
	
	pipe(fd);
	pid = fork();
	if(pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
	else {
		close(fd[0]);
		dup2(fd[1], 1);
		execve(path, command, NULL);
	}
}