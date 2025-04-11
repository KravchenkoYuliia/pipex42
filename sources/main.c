/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/11 18:00:10 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int	ft_check_file_existing(char *file)
{
	int	fd;

	fd = open(file, O_RDWR);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	main(int ac, char **av, char **envp)
{
	(void)envp;
	(void)ac;
	int	infile;
	int	outfile;

	infile = ft_check_file_existing(av[1]);
	if (infile == -1)
	{
		perror("Error\nInfile does not exist");
		exit(EXIT_FAILURE);
	}
	outfile = ft_check_file_existing(av[4]);
	if (outfile == -1)
	{
		perror("Error\nOutfile does not exist");
		ft_exit(infile, 0);
	}
	close(infile);
	close(outfile);
	/*
	int fd[2];
	pipe(fd);
	int id = fork();
	char *args1[] = {"/bin/ls", NULL};
	char *args2[] = {"/bin/grep", "test",  NULL};
	
	if (id == 0)
	{
		close(fd[1]);
		ft_printf("I'm a child process and I read from fd[0]\n");
		dup2(fd[0], 0);
		execve(args2[0], args2, NULL);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		ft_printf("parent process and I write in fd[1]\n");
		dup2(fd[1], 1);
		close(fd[1]);
		execve(args1[0], args1, NULL);
	}*/
}
