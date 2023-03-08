#include "pipex.h"
#include <sys/stat.h>

char **find_path(char **envp)
{
	size_t i;
	char path[6];
	char **paths;

	i = 0;
	ft_memcpy(&path, "PATH=\0", 6);
	while(envp[i])
	{
		if(ft_strncmp(envp[i], path, ft_strlen(path)))
		{
			i++;
			continue;
		}
		break;
	}
	if(!ft_strncmp(envp[i], path, ft_strlen(path)))
	{
		envp[i][3] = '.';
		envp[i][4] = ':';
		envp[i] += 3; 
		paths = ft_split(envp[i], ':');
		return (paths);
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	int fd0;
	int fd1;
	int flags;

	execute_here_doc(argc, argv);
	// perror(test);
	// flags = O_RDWR | O_APPEND | O_CREAT;
	// fd0 = open("in", flags, 0777);
	// fd1 = open("out", flags, 0777);
	// dup2(0, fd0);
	// dup2(1, fd1);
	// write(fd1, "pipe heredoc>", 13);
	// test = ;
	// test = get_next_line(fd0);
	// while(test)
	// {
	// 	test = get_next_line(fd0);
	// 	if(ft_strchr(test, '\n'))
	// 		write(fd1, "pipe heredoc>", 13);
	// }
	// int fd;
	// int fd2;
	// char **paths;
	
	// // if(argc < 5)
	// //     return (1);
	// if(!access(argv[1], R_OK))
	// {
	// 	paths = find_path(envp);
	// 	if(!paths)
	// 		return (0);
	// 	execute_pipe(argc, argv, envp, paths);
	// 	// int i = 0;
	// 	// while(paths[i])
	// 	// {
	// 	// 	printf("%s\n", paths[i]);
	// 	// 	i++;
	// 	// }
	// } else if(!ft_strcmp(argv[1], "here_doc"))
	// {

	// }
	return (0);
}