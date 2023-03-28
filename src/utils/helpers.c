/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:12:33 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/12 23:04:50 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*exec_join_check(char *path, char **command)
{
	char	*temp_path;
	char	*check_path;

	temp_path = ft_strjoin(path, "/");
	if (!temp_path)
		return (NULL);
	check_path = ft_strjoin(temp_path, command[0]);
	free_s(&temp_path);
	if (!access(check_path, X_OK))
	{
		free_d(&command);
		return (check_path);
	}
	free_s(&check_path);
	return (0);
}

char	*is_command_executable(char *command, char **paths)
{
	size_t	i;
	char	**splited_cmd;
	char	*check_path;

	i = 0;
	splited_cmd = split_cmd(command);
	if (!splited_cmd)
		return (NULL);
	if (!access(splited_cmd[0], X_OK))
	{
		check_path = ft_strdup(splited_cmd[0]);
		free_d(&splited_cmd);
		return (check_path);
	}
	while (paths[i])
	{
		check_path = exec_join_check(paths[i], splited_cmd);
		if (check_path)
			return (check_path);
		free_s(&check_path);
		i++;
	}
	return (free_d(&splited_cmd));
}

char	**find_path(char **envp)
{
	size_t	i;
	char	path[6];
	char	**paths;

	i = 0;
	ft_memcpy(&path, "PATH=\0", 6);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], path, ft_strlen(path)))
		{
			i++;
			continue ;
		}
		break ;
	}
	if (!ft_strncmp(envp[i], path, ft_strlen(path)))
	{
		envp[i][3] = '.';
		envp[i][4] = ':';
		envp[i] += 3;
		paths = ft_split(envp[i], ':');
		return (paths);
	}
	return (NULL);
}

void	file_check(int *argc, char ***argv)
{
	int	fd0;
	int	fd1;
	int	last_index;

	last_index = (*argc - 1);
	if (!ft_strcmp((*argv)[1], "here_doc"))
	{
		fd1 = open((*argv)[last_index], O_WRONLY | O_APPEND | O_CREAT, 0755);
		execute_here_doc(argc, argv);
		duplicate_fd(fd1, 1);
		return ;
	}
	if(!permission_check(argc, argv))
		fd0 = open((*argv)[1], O_RDONLY);
	else
	{
		fd0 = open("/dev/null", O_RDONLY);
		*argv += 1;
		*argc -= 1;
	}
	fd1 = open((*argv)[last_index], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	dup2(fd0, 0);
	dup2(fd1, 1);
	*argv += 2;
	*argc -= 3;
}
