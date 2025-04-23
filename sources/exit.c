/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:43:36 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/23 13:36:51 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(char *msg, char *cmd)
{
	write(2, msg, ft_strlen(msg));
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int	ft_count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	*ft_free_args(char **args)
{
	int	i;
	int	numb_of_arg;

	i = 0;
	numb_of_arg = ft_count_args(args);
	while (i < numb_of_arg)
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (NULL);
}

void	ft_close(int fd, int pipe[2])
{
	if (fd >= 0)
		close(fd);
	if (pipe >= 0)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
}

void	ft_close_exit(int fd, int pipe[2])
{
	ft_close(fd, pipe);
	exit(EXIT_FAILURE);
}
