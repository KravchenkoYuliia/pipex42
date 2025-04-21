/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:30:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/19 15:41:18 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int    ft_check_infile(char *filename, int pipe[2])
{
	int     fd;

        if (access(filename, F_OK) == -1)
        {
                ft_close(-1, pipe);
                ft_exit("pipex: no such file or directory: ", filename);
        }
        fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
                ft_close(-1, pipe);
                ft_exit("pipex: permission denied: ", filename);
        }
	return (fd);
}

void    ft_check_abs_path(char **args, int file, int pipe[2], char *cmd)
{
        if (ft_strchr(args[0], '/') && (access(args[0], X_OK) == -1))
        {
                ft_free_args(args);
                ft_close(file, pipe);
                ft_exit("pipex: no such file or directory: ", cmd);
        }
}


void    ft_child_for_first_cmd(char *cmd1, int pipe[2], char **av, char **env)
{
	int	fd;

	fd = ft_check_infile(av[1], pipe);
	char    **args;

        args = ft_split(cmd1, ' ');
        ft_check_abs_path(args, fd, pipe, cmd1);
        if (!ft_strchr(args[0], '/'))
                args[0] = ft_get_absolute_path(env, args[0]);
        if (args[0] == NULL)
        {
                ft_free_args(args);
                ft_close(fd, pipe);
                ft_exit("pipex: command not found: ", cmd1);
        }
        dup2(fd, STDIN_FILENO);
        dup2(pipe[1], STDOUT_FILENO);
        ft_close(fd, pipe);
        if (execve(args[0], args, NULL) == -1)
        {
                ft_free_args(args);
                perror("pipex");
                exit(EXIT_FAILURE);
        }
}
int    ft_check_outfile(char *filename, int pipe[2])
{
        int     fd;

        fd = open(filename,
                        O_RDWR | O_CREAT | O_TRUNC,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
        {
                ft_close(-1, pipe);
		perror("pipex");
		exit(EXIT_FAILURE);
        }
        return (fd);
}

void	ft_child_for_last_cmd(char *outfile, char *last_cmd, int pipe[2], char **env)
{
	int	fd;
	char    **args;

	fd = ft_check_outfile(outfile, pipe);
        args = ft_split(last_cmd, ' ');
        ft_check_abs_path(args, fd, pipe, last_cmd);
        if (!ft_strchr(args[0], '/'))
                args[0] = ft_get_absolute_path(env, args[0]);
        if (args[0] == NULL)
        {
                ft_free_args(args);
                ft_close(fd, pipe);
                ft_exit("pipex: command not found: ", last_cmd);
        }
        dup2(fd, STDOUT_FILENO);
        ft_close(fd, pipe);
        if (execve(args[0], args, NULL) == -1)
        {
                ft_free_args(args);
                perror("pipex");
                exit(EXIT_FAILURE);
        }
}

void	ft_child_process()
{	
	printf("Doing middle cmd\n");
	exit(EXIT_SUCCESS);
}
	
	
	/*
        char    **args;

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
*/
