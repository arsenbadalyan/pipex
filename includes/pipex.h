/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:06:32 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/05 20:40:09 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

// Standard C Libs
#include <stdio.h> // TODO: DELETE
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "libft.h"


// Execute Pipe
void execute_pipe(int argc, char **argv, char **envp, char **paths);

// Helpers
char *read_file(char *path);
char	*exec_join_check(char *path, char **command);
char *is_command_executable(char *command, char **paths);

// Free functions
char *free_s(char **addr);
char *free_d(char ***addr);

#endif