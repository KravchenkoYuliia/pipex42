/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/13 19:16:32 by yukravch         ###   ########.fr       */
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
	int fd = open(av[4], O_WRONLY | O_CREAT, 00700);
	if (fd == -1)
	{
		ft_printf("Fail");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
