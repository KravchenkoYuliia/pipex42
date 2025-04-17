/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/17 17:41:45 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"


void	ft_check_file1_exists(char *file1)
{
	if (access(file1, F_OK) == -1)
	{
		perror("pipex");
		write(2, ": ", 2);
		write(2, file1, ft_strlen(file1));
		exit(EXIT_FAILURE);
	}
}
/*
int	ft_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (1);
	else
		return (0);
}
*/
int	ft_check_access(char *cmd_path)
{
	if (access(cmd_path, X_OK) == 0)
		return (1);
	else
		return (0);
}

void	ft_first_child(int file1_fd, char *cmd1, int pipe[2])
{
	char	**args;
	args = ft_split(cmd1, ' ');
	if (ft_strchr(args[0], '/') && !ft_check_access(args[0]))
	{
		perror("pipex1");
		write(2, ":", 1);
		write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}

	dup2(file1_fd, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(file1_fd);
	close(pipe[0]);
	close(pipe[1]);
	if (execve(args[0], args, NULL) == -1)
	{
		perror("pipex1");
		exit(EXIT_FAILURE);
	}
}

void	ft_second_child(int file_fd2, char *cmd2, int pipe_read, int pipe_write)
{
	char	**args;

	args = ft_split(cmd2, ' ');
	if (ft_strchr(args[0], '/') && !ft_check_access(args[0]))
	{
		perror("pipex2");
		exit(EXIT_FAILURE);
	}
	dup2(pipe_read, STDIN_FILENO);
	dup2(file_fd2, STDOUT_FILENO);
	close(file_fd2);
	close(pipe_read);
	close(pipe_write);
	if (execve(args[0], args, NULL) == -1)
	{
		perror("pipex2");
	}
}


/*
void	ft_parent_process(char **av, char **env)
{
	(void)av;
	(void)env;
	ft_pipe();
	ft_fork1();
	ft_fork2();
}
*/

void	ft_test(char **env)
{
	int	i;
	char	*env_line_with_path;
	char	**all_files_path;
	//char	*file_path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	env_line_with_path = env[i] + 5;
	all_files_path = ft_split(env_line_with_path, ':');
	i = 0;
	while (all_files_path[i])
	{
		file_path = ft_strjoin(a);
		printf("path: %s\n", all_files_path[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	(void) env;
	int	file1_fd;
	int	file2_fd;
	int	pipe_end[2];
	int	pid1;
	int	pid2;
	
	ft_test(env);
	if (ac != 5)
	{
		write(2, "Not enough arguments", 20);
		exit(EXIT_FAILURE);
	}
	
	//ft_parent_process(av, env);
	
	ft_check_file1_exists(av[1]);
	pipe(pipe_end);

	pid1 = fork();
	if (pid1 == 0)
	{
		file1_fd = open(av[1], O_RDONLY);
		printf("I'm first child, I execute first command\n");
		ft_first_child(file1_fd, av[2], pipe_end);
	}
	
	pid2 = fork();
	if (pid2 == 0)
	{
		file2_fd = open(av[4], 
				O_RDWR | O_CREAT | O_TRUNC, 
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		printf("I'm second child, I execute second command\n");
		ft_second_child(file2_fd, av[3], pipe_end[0], pipe_end[1]);
	}
	
	close(pipe_end[0]);
	close(pipe_end[1]);
	
	waitpid(pid1, NULL, 0);
	printf("I'm parent: First child (pid %d) finished\n\n", pid1);
	waitpid(pid2, NULL, 0);
	printf("I'm parent: Second child (pid %d) finished\n", pid2);
	
}
