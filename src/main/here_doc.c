#include "pipex.h"

void wait_to_limiter(int argc, char **argv, int fd)
{
	char *limiter;
	char *buffer;
	char *temp;

	limiter = argv[1];
	buffer = NULL;
	write(1, ">", 1);
	while(1)
	{
		temp = get_next_line(0);
		buffer = ft_realloc(&buffer, &temp);
		if(temp && temp[0] == '\n')
		{
			free_s(&temp);
			if(!ft_strncmp(buffer, limiter, ft_strlen(limiter)) && ((ft_strlen(buffer) - 1) == ft_strlen(limiter)))
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

void execute_here_doc(int argc, char **argv)
{
	int fd;
	char *file;

	fd = open(".read_here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	wait_to_limiter(argc, argv, fd);
}