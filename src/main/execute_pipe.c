/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:16:13 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/12 23:00:30 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_pipe(int argc, char **argv, char **envp, char **paths)
{
	size_t	index;
	char	*path;
	char	**command_arr;
	pid_t	pid;

	index = 0;
	while (index < argc)
	{
		command_arr = ft_split(argv[index], ' ');
		path = is_command_executable(command_arr[0], paths);
		if (!path)
			write_exception(404, command_arr[0], 0);
		if (index != (argc - 1))
			pipe_commands(argv, path, command_arr, envp);
		else
		{
			pid = fork();
			if (!pid)
				exit(execve(path, command_arr, envp));
		}
		free_d(&command_arr);
		index++;
	}
}

void	pipe_commands(char **argv, char *path, char **command, char **envp)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		exit(execve(path, command, envp));
	}
}
