/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:06:32 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/12 20:21:59 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Standard C Libs
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"
# include "get_next_line.h"

// Here Doc FileName
# define IN_FILE ".read_here_doc"

// Execute Pipe
void	pipe_commands(char *path, char **command, char **envp);
void	execute_pipe(int argc, char **argv, char **envp, char **paths);

// Execute here_doc
void	wait_to_limiter(char *limiter, int fd);
void	execute_here_doc(int *argc, char ***argv);

// Helpers
char	*exec_join_check(char *path, char **command);
char	*is_command_executable(char *command, char **paths);
char	**find_path(char **envp);
void	file_check(int *argc, char ***argv);

// Free functions
char	*free_s(char **addr);
char	*free_d(char ***addr);

// Utilities
void	write_exception(int errno, char *addn, char *addn2, int is_exit);
void	duplicate_fd(int fd_from, int fd_to);
char	**split_cmd(char *command);
int		permission_check(int *argc, char ***argv);

#endif