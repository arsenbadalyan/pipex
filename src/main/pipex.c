#include "pipex.h"

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
	int fd;
	char **paths;

	// if(argc < 5)
	//     return (1);
	if(!access(argv[1], R_OK))
	{
		paths = find_path(envp);
		if(!paths)
			return (0);
		execute_pipe(argc, argv, envp, paths);
		// int i = 0;
		// while(paths[i])
		// {
		// 	printf("%s\n", paths[i]);
		// 	i++;
		// }
	} else if(!ft_strcmp(argv[1], "here_doc"))
	{

	}
	return (0);
}