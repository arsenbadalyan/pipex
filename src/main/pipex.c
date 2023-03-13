/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:19:09 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/12 17:51:47 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**paths;

	if (argc < 5)
		return (1);
	file_check(&argc, &argv);
	paths = find_path(envp);
	if (!paths)
		return (0);
	execute_pipe(argc, argv, envp, paths);
	unlink(IN_FILE);
	system("leaks pipex");
	return (0);
}
