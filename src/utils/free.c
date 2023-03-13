/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:21:28 by arsbadal          #+#    #+#             */
/*   Updated: 2023/03/12 16:22:29 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_s(char **addr)
{
	free(*addr);
	*addr = 0x0;
	return (NULL);
}

char	*free_d(char ***addr)
{
	size_t	i;

	i = 0;
	if (*addr)
	{
		while ((*addr)[i])
			free_s(&((*addr)[i]));
		free(*addr);
		*addr = 0;
	}
	return (NULL);
}
