/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:12:33 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/05 20:40:27 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_file(char *path)
{
	size_t	size;
	int		fd;
	char	c;
	char	*output;

	size = 0;
	fd = open(path, O_RDONLY);
	while (read(fd, &c, 1))
		size++;
	close(fd);
	output = (char *)malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	fd = open(path, O_RDONLY);
	read(fd, output, size);
	return (output);
}

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
	splited_cmd = NULL;
	splited_cmd = ft_split(command, ' ');
	if (!splited_cmd)
		return (NULL);
	if (!splited_cmd[0] || !splited_cmd[0][0])
		return (free_d(&splited_cmd));
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
		i++;
	}
	return (free_d(&splited_cmd));
}
