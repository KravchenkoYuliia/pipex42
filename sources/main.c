/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/11 14:00:28 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int	main()
{
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
	}
}
