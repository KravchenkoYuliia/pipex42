/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/16 18:54:17 by yukravch         ###   ########.fr       */
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

void	ft_first_child(int file1_fd, char *cmd1, int pipe_read, int pipe_write)
{
	(void)cmd1;
	char	*args[3] = {"ls", "-l", NULL};

	close(pipe_read);
	dup2(file1_fd, STDIN_FILENO);
	dup2(pipe_write, STDOUT_FILENO);
	if (execve("/bin/ls", args, NULL) == -1)
	{
		perror("pipex");
		ft_printf("Fail");
	}
}

void	ft_second_child(int file_fd2, char *cmd2, int pipe_read, int pipe_write)
{
	(void)cmd2;
	(void)file_fd2;
	char	*args[3] = {"wc", "-l", NULL};

	close(pipe_write);
	dup2(pipe_read, STDIN_FILENO);
	dup2(file_fd2, STDOUT_FILENO);
	if (execve("/bin/wc", args, NULL) == -1)
	{
		perror("pipex");
		ft_printf("Fail");
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
int	main(int ac, char **av, char **env)
{
	(void) env;
	int	file1_fd;
	int	file2_fd;
	//t_pipe_end	*pipex;
	int	pipe_end[2];
	int	pid1;
	int	pid2;
	
	if (ac != 5)
	{
		write(2, "Not enough arguments", 20);
		exit(EXIT_FAILURE);
	}
	ft_check_file1_exists(av[1]);
	//ft_parent_process(av, env);
	//pipex = (t_pipe_end *)malloc(sizeof(t_pipe_end));
	pipe(pipe_end);
	//pipe((int *)pipex);
	pid1 = fork();
	file1_fd = open(av[1], O_RDONLY);
	if (pid1 == 0)
	{
		ft_printf("I'm first child, I execute first command\n");
		ft_first_child(file1_fd, av[2], pipe_end[0], pipe_end[1]);
	}
	waitpid(pid1, NULL, 0);
	close(file1_fd);
	ft_printf("I'm parent: First child (pid %d) finished\n\n", pid1);
	
	pid2 = 0;
	file2_fd = 0;
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}

	file2_fd = open(av[4], O_WRONLY | O_CREAT, 00700);
	if (pid2 == 0)
	{
		ft_printf("I'm second child, I execute second command\n");
		ft_second_child(file2_fd, av[4], pipe_end[0], pipe_end[1]);
	}
	close(pipe_end[0]);
	close(pipe_end[1]);
	waitpid(pid2, NULL, 0);
	
	close(file2_fd);
	ft_printf("I'm parent: Second child (pid %d) finished\n", pid2);
}
