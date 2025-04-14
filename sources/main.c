/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/14 14:55:21 by yukravch         ###   ########.fr       */
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

void	ft_read_from_file1(char *file1, char *cmd1)
{
	(void)file1;
	int	fd[2];

	pipe(fd);		//fd[0] - read from it
				//fd[1] - write on it
	
	fd[0] = open(file1, O_RDONLY);
	dup2(5, fd[0]);
	ft_printf("fd[0] = %d", 5);
	char *args[] = {"ls", "-l", NULL};
	if (execve(cmd1, args, 5) == -1)
		ft_printf("Fail\n");
	
}

int	main(int ac, char **av, char **envp)
{
	(void)envp;
	(void)ac;
	
	if (ac != 5)
	{
		write(2, "Not enough arguments", 20);
		exit(EXIT_FAILURE);
	}
	ft_check_file1_exists(av[1]);
	
	int pid1 = fork();
	if (pid1 == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		ft_printf("I'm first child, I read from file1\n");
		ft_read_from_file1(av[1], av[2]);
		exit(EXIT_SUCCESS);
	}
	
	waitpid(pid1, NULL, 0);
	ft_printf("I'm parent: First child (pid %d) finished\n\n", pid1);

	int	pid2 = fork();
	if (pid2 == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}

	if (pid2 == 0)
	{
		ft_printf("I'm second child, I write on file2\n");
		exit(EXIT_SUCCESS);
	}

	waitpid(pid2, NULL, 0);
	ft_printf("I'm parent: Second child (pid %d) finished\n", pid2);
	





	int file2 = open(av[4], O_WRONLY | O_CREAT, 00700);
	if (file2 == -1)
	{
		ft_printf("Fail");
		exit(EXIT_FAILURE);
	}
	close(file2);
}
