/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:49:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/02/17 12:36:07 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static char	**gnl_get_internal_buffer(void)
{
	static char *str[1024];
	return (str);
}

void	free_gnl_buffer(int fd)
{
	char **str = gnl_get_internal_buffer();
	if (str[fd])
	{
		free(str[fd]);
		str[fd] = NULL;
	}
}

char	*get_next_line(int fd)
{
	char	**reserve;
	char		*line;

	reserve = gnl_get_internal_buffer();
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reserve[fd] = ft_read_buffer(fd, reserve[fd]);
	if (!reserve[fd])
		return (free(reserve[fd]), NULL);
	line = ft_get_line(reserve[fd]);
	if (!line)
		return (NULL);
	reserve[fd] = ft_cut_line(reserve[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd = open("variable_nls.txt", O_RDONLY);
	char *line = NULL;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
}
*/
