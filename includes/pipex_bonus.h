/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:33:27 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/23 13:40:00 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

void	ft_exit(char *msg, char *cmd);
char	*ft_get_absolute_path(char **env, char *cmd);
int		ft_count_args(char **args);
void	*ft_free_args(char **args);
void	ft_close(int fd, int pipe[2]);
int		ft_check_infile(char *filename, int pipe[2]);
void	ft_middle_child(char *cmd, int pipe[2], char **env);
void	ft_child_for_first_cmd(char *cmd1, int pipe[2], char **av, char **env);
void	ft_child_for_last_cmd(char *outfile,
			char *last_cmd, int pipe[2], char **env);
void	ft_check_abs_path(char **args, int file, int pipe[2], char *cmd);
void	ft_handle_heredoc(char **av);
void	ft_remove_limiter(int *ac, char **av);
int		ft_check_outfile(char *outfile, int pipe[2]);
int		ft_check_infile(char *filename, int pipe[2]);

#endif
