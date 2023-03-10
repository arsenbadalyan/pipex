#include "pipex.h"

void wait_to_limiter(int argc, char **argv, char *limiter, int fd)
{
	char *buffer;

	write(1, ">", 1);
	while(1)
	{
		buffer = get_next_line(0);
		if (!buffer)
		{
			perror("memory");
			exit(1);
		}
		if (buffer && ft_strchr(buffer, '\n'))
		{
			if (!ft_strncmp(buffer, limiter, ft_strlen(limiter)) && ((ft_strlen(buffer) - 1) == ft_strlen(limiter)))
			{
				free_s(&buffer);
				break;
			} else {
				write(fd, buffer, ft_strlen(buffer));
			}
			free_s(&buffer);
			write(1, ">", 1);
		}
	}	
}

void execute_here_doc(int *argc, char ***argv)
{
	int fd;
	char *file;

	fd = open(".read_here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	wait_to_limiter(*argc, *argv, *((*argv) + 2), fd);
	dup2(fd, 0);
	close(fd);
	*argc-=2;
	*argv+=2;
}