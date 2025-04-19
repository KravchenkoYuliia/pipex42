/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:33:27 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/19 15:43:33 by yukravch         ###   ########.fr       */
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


void    ft_exit(char *msg, char *cmd);
char    *ft_get_absolute_path(char **env, char *cmd);
int             ft_count_args(char **args);
void    *ft_free_args(char **args);
void    ft_close(int fd, int pipe[2]);
void    ft_start_of_new_process(int cmd_num, char **av, char **env, int pipe[2]);
void    ft_start_of_new_process2(int cmd_num, char **av, char **env, int pipe[2]);
void    ft_first_child(int file1_fd, char *cmd1, int pipe[2], char **env);
void    ft_second_child(int file2_fd, char *cmd2, int pipe[2], char **env);
void    ft_check_abs_path(char **args, int file, int pipe[2], char *cmd);

#endif
