/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/18 14:51:48 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	ft_first_child(int file1_fd, char *cmd1, int pipe[2], char **env)
{
	char	**args;
	args = ft_split(cmd1, ' ');
	if (ft_strchr(args[0], '/') && (access(args[0], X_OK) == -1))
	{
		exit(-1);/*
		ft_free_args(args);
		close(file1_fd);
		close(pipe[0]);
		close(pipe[1]);
		ft_exit(args[0]);*/
	}
	if (!ft_strchr(args[0], '/'))
		args[0] = ft_get_absolute_path(env, args[0]);
	/*if (args[0] == NULL)
	{
		ft_free_args(args);
		close(file1_fd);
		close(pipe[0]);
		close(pipe[1]);
		exit(-1);
	}*/
	dup2(file1_fd, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(file1_fd);
	close(pipe[0]);
	close(pipe[1]);
	if (execve(args[0], args, NULL) == -1)
	{
		ft_free_args(args);
		exit(EXIT_FAILURE);
	}
}

void	ft_second_child(int file2_fd, char *cmd2, int pipe[2], char **env)
{
	char	**args;

	args = ft_split(cmd2, ' ');
	if (ft_strchr(args[0], '/') && (access(args[0], X_OK) == -1))
	{
		ft_free_args(args);
		close(file2_fd);
		close(pipe[0]);
		close(pipe[1]);	
		perror("pipex2");
		exit(EXIT_FAILURE);
	}
	if (!ft_strchr(args[0], '/'))
		args[0] = ft_get_absolute_path(env, args[0]);
	if (args[0] == NULL)
	{
		ft_free_args(args);
		close(file2_fd);
		close(pipe[0]);
		close(pipe[1]);
		exit(-1);
	}
		
	dup2(pipe[0], STDIN_FILENO);
	dup2(file2_fd, STDOUT_FILENO);
	close(file2_fd);
	close(pipe[0]);
	close(pipe[1]);
	if (execve(args[0], args, NULL) == -1)
	{
		ft_free_args(args);
		perror("pipex2");
		exit(EXIT_FAILURE);
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

char	*ft_get_absolute_path(char **env, char *cmd)
{
	int	i;
	char	*env_line_with_path;
	char	**all_files_path;
	char	*add_slash;
	char	*file_path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	env_line_with_path = env[i] + 5;
	all_files_path = ft_split(env_line_with_path, ':');
	if (!all_files_path)
		return (NULL);
	i = 0;
	while (all_files_path[i])
	{
		add_slash = ft_strjoin(all_files_path[i], "/");
		file_path = ft_strjoin(add_slash, cmd);
		if (access(file_path, X_OK) == 0)
			return (file_path);
		i++;
	}
	free(file_path);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	int	file1_fd;
	int	file2_fd;
	int	pipe_end[2];
	int	pid1;
	int	pid2;
	if (ac != 5)
	{
		write(2, "Not enough arguments", 20);
		exit(EXIT_FAILURE);
	}
	
	//ft_parent_process(av, env);
	if (access(av[1], F_OK) == -1)
		ft_exit("file1");
	pipe(pipe_end);

	pid1 = fork();
	if (pid1 == 0)
	{
		file1_fd = open(av[1], O_RDONLY);
		ft_first_child(file1_fd, av[2], pipe_end, env);
	}
	
	pid2 = fork();
	if (pid2 == 0)
	{
		file2_fd = open(av[4], 
				O_RDWR | O_CREAT | O_TRUNC, 
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		ft_second_child(file2_fd, av[3], pipe_end, env);
	}
	
	close(pipe_end[0]);
	close(pipe_end[1]);
	
	waitpid(pid1, NULL, 0);
	printf("I'm parent: First child (pid %d) finished\n\n", pid1);
	waitpid(pid2, NULL, 0);
	printf("I'm parent: Second child (pid %d) finished\n", pid2);
	
}
