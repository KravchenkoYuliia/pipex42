/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:08:33 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/19 14:12:06 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_start_of_new_process(char **av, char **env, int pipe[2])
{
	int	file1_fd;

	if (access(av[1], F_OK) == -1)
	{
		ft_close(-1, pipe);
		ft_exit("pipex: no such file or directory: ", av[1]);
	}
	file1_fd = open(av[1], O_RDONLY);
	if (file1_fd == -1)
	{
		ft_close(-1, pipe);
		ft_exit("pipex: permission denied: ", av[1]);
	}
	ft_first_child(file1_fd, av[2], pipe, env);
}

void	ft_check_abs_path(char **args, int file, int pipe[2], char *cmd)
{
	if (ft_strchr(args[0], '/') && (access(args[0], X_OK) == -1))
	{
		ft_free_args(args);
		ft_close(file, pipe);
		ft_exit("pipex: no such file or directory: ", cmd);
	}
}

void	ft_first_child(int file1_fd, char *cmd1, int pipe[2], char **env)
{
	char	**args;

	args = ft_split(cmd1, ' ');
	ft_check_abs_path(args, file1_fd, pipe, cmd1);
	if (!ft_strchr(args[0], '/'))
		args[0] = ft_get_absolute_path(env, args[0]);
	if (args[0] == NULL)
	{
		ft_free_args(args);
		ft_close(file1_fd, pipe);
		ft_exit("pipex: command not found: ", cmd1);
	}
	dup2(file1_fd, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	ft_close(file1_fd, pipe);
	if (execve(args[0], args, NULL) == -1)
	{
		ft_free_args(args);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}
