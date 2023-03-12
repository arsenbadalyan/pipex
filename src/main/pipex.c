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

void duplicate_fd(int fd_from, int fd_to)
{
	dup2(fd_from, fd_to);
	close(fd_from);
}

void file_check(int *argc, char ***argv)
{
	int fd0;
	int fd1;
	int last_index;

	last_index = (*argc - 1);
	if (!access(*(*argv + last_index), F_OK) && access(*(*argv + last_index), W_OK))
		write_exception(13);
	if (access(**argv, R_OK) == -1 && !ft_strcmp(*(*argv + 1), "here_doc"))
		write_exception(13);
	if (!ft_strcmp(*(*argv + 1), "here_doc"))
	{
		fd1 = open(*(*argv + last_index), O_WRONLY | O_APPEND | O_CREAT, 0755);
		execute_here_doc(argc, argv);
		duplicate_fd(fd1, 1);
		return;
	}
	fd0 = open(*(*argv + last_index), O_RDONLY);
	fd1 = open(*(*argv + last_index), O_WRONLY | O_TRUNC | O_CREAT, 0755);
	duplicate_fd(fd0, 0);
	duplicate_fd(fd1, 1);
	*argv++;
	*argc--;
}

int main(int argc, char **argv, char **envp)
{
	char **paths;
	
	if(argc < 5)
		return (1);
	paths = find_path(envp);
	if (!paths)
		return (0);
	file_check(&argc, &argv);
	execute_pipe(argc, argv, envp, paths);
	// system("leaks pipex");
	return (0);
}