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

	index = 1;
	while(index < argc)
	{
		path = is_command_executable(argv[index], paths);
		if(!path)
			write_exception(404);
		
		index++;
	}
}

// void pipe_commands(int argc, char **argv, )
// {
// 	int pid;
// 	int fd[2];

// 	pipe(fd);
// 	pid = fork();
// 	// if(pid == -1)
// 	// {
// 	// 	perror("fork");
// 	// 	exit(1);
// 	// }
// 	if(pid)
// 	{

// 	}
// 	else {
// 		close(fd[1]);

// 		close(fd[0]);
// 	}
// }