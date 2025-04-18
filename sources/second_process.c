/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:30:26 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/18 20:07:55 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_start_of_new_process2(char **av, char **env, int pipe[2])
{
	int file2_fd;

	file2_fd = open(av[4],
                                O_RDWR | O_CREAT | O_TRUNC,
                                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_second_child(file2_fd, av[3], pipe, env);
}

void    ft_second_child(int file2_fd, char *cmd2, int pipe[2], char **env)
{
        char    **args;

        args = ft_split(cmd2, ' ');
	ft_check_abs_path(args, file2_fd, pipe, cmd2);
        if (!ft_strchr(args[0], '/'))
                args[0] = ft_get_absolute_path(env, args[0]);
        if (args[0] == NULL)
        {
                ft_free_args(args);
                ft_close(file2_fd, pipe);
                ft_exit("pipex: command not found: ", cmd2);
        }
        dup2(pipe[0], STDIN_FILENO);
        dup2(file2_fd, STDOUT_FILENO);
        ft_close(file2_fd, pipe);
        if (execve(args[0], args, NULL) == -1)
        {
                ft_free_args(args);
                perror("pipex");
                exit(EXIT_FAILURE);
        }
}
