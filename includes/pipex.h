/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:19:12 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/23 13:38:09 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

void	ft_exit(char *msg, char *cmd);
char	*ft_get_absolute_path(char **env, char *cmd);
int		ft_count_args(char **args);
void	*ft_free_args(char **args);
void	ft_close(int fd, int pipe[2]);
void	ft_start_of_new_process(char **av, char **env, int pipe[2]);
void	ft_start_of_new_process2(char **av, char **env, int pipe[2]);
void	ft_first_child(int file1_fd, char *cmd1, int pipe[2], char **env);
void	ft_second_child(int file2_fd, char *cmd2, int pipe[2], char **env);
void	ft_check_abs_path(char **args, int file, int pipe[2], char *cmd);
void	ft_close_exit(int fd, int pipe[2]);

#endif
