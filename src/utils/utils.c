/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:23:29 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/12 22:49:06 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_exception(int errno, char *addn, char *addn2)
{
	char	*error;

	if (errno == 404)
		error = "command not found: ";
	else
		error = strerror(errno);
	ft_putstr_fd("zsh: ", 2);
	ft_putstr_fd(error, 2);
	if (addn)
	{
		if (errno != 404)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(addn, 2);
	}
	if (addn2)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(addn2, 2);
	}
	ft_putstr_fd("\n", 2);
	if (errno < 128)
		exit(errno);
}

void	duplicate_fd(int fd_from, int fd_to)
{
	dup2(fd_from, fd_to);
	close(fd_from);
}

char	**split_cmd(char *command)
{
	char	**splited_cmd;

	splited_cmd = NULL;
	splited_cmd = ft_split(command, ' ');
	if (!splited_cmd)
		return (NULL);
	if (!splited_cmd[0] || !splited_cmd[0][0])
	{
		free_d(&splited_cmd);
		return (NULL);
	}
	return (splited_cmd);
}

void	permission_check(int *argc, char ***argv)
{
	int	last_index;

	last_index = (*argc - 1);
	if (ft_strcmp((*argv)[1], "here_doc")
		&& access((*argv)[1], F_OK) == -1)
		write_exception(2, (*argv)[1], 0);
	if (ft_strcmp((*argv)[1], "here_doc")
		&& access((*argv)[1], R_OK) == -1)
	{
		if (!access((*argv)[last_index], F_OK)
		&& access((*argv)[last_index], W_OK))
			write_exception(13, (*argv)[1], (*argv)[last_index]);
		write_exception(13, (*argv)[1], 0);
	}	
	if (!access((*argv)[last_index], F_OK)
		&& access((*argv)[last_index], W_OK))
		write_exception(13, (*argv)[last_index], 0);
}
