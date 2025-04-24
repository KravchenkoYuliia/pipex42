/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:32:54 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/24 12:56:51 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_handle_heredoc(char **av)
{
	int		fd;
	int		diff;
	char	*line;

	fd = open("heredoc",
			O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return ;
		diff = ft_strncmp(line, av[2], ft_strlen(line));
		if (diff == 0 || diff == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	get_next_line(-42);
	close(fd);
}

void	ft_remove_limiter(int *ac, char **av)
{
	int	i;

	i = 2;
	while (i < *ac)
	{
		av[i] = av[i + 1];
		i++;
	}
	*ac = *ac - 1;
}
