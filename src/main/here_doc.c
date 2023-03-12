/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:17:33 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/12 18:29:02 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_to_limiter(int argc, char **argv, char *limiter, int fd)
{
	char	*buffer;

	write(1, ">", 1);
	while (1)
	{
		buffer = get_next_line(0);
		if (!buffer)
			write_exception(12, 0, 0);
		if (buffer && ft_strchr(buffer, '\n'))
		{
			if (!ft_strncmp(buffer, limiter, ft_strlen(limiter))
				&& ((ft_strlen(buffer) - 1) == ft_strlen(limiter)))
			{
				free_s(&buffer);
				break ;
			}
			else
				write(fd, buffer, ft_strlen(buffer));
			write(1, ">", 1);
		}
		free_s(&buffer);
	}	
}

void	execute_here_doc(int *argc, char ***argv)
{
	int		fd;
	char	*file;

	fd = open(IN_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	wait_to_limiter(*argc, *argv, *((*argv) + 2), fd);
	close(fd);
	fd = open(IN_FILE, O_RDONLY);
	duplicate_fd(fd, 0);
	close(fd);
	*argc -= 4;
	*argv += 3;
}
