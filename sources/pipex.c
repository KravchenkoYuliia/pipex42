/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:18:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/23 13:37:41 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_add_slash_cmd(char **all_files_path, char *cmd)
{
	int		i;
	char	*add_slash;
	char	*file_path;

	i = 0;
	while (all_files_path[i])
	{
		add_slash = ft_strjoin(all_files_path[i], "/");
		file_path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (access(file_path, X_OK) == 0)
		{
			free(cmd);
			ft_free_args(all_files_path);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free(cmd);
	ft_free_args(all_files_path);
	return (NULL);
}

char	*ft_get_absolute_path(char **env, char *cmd)
{
	int		i;
	char	*env_line_with_path;
	char	**all_files_path;
	char	*file_path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	env_line_with_path = env[i] + 5;
	all_files_path = ft_split(env_line_with_path, ':');
	if (!all_files_path)
		return (NULL);
	file_path = ft_add_slash_cmd(all_files_path, cmd);
	return (file_path);
}

void	ft_parent_process(char **av, char **env)
{
	int		pipe_end[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_end) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		ft_close_exit(-1, pipe_end);
	if (pid1 == 0)
		ft_start_of_new_process(av, env, pipe_end);
	pid2 = fork();
	if (pid2 == -1)
	{
		waitpid(pid1, NULL, 0);
		ft_close_exit(-1, pipe_end);
	}
	if (pid2 == 0)
		ft_start_of_new_process2(av, env, pipe_end);
	ft_close(-1, pipe_end);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char **av, char **env)
{	
	if (ac != 5)
	{
		write(2, "Write 4 arguments\n", 18);
		exit(EXIT_FAILURE);
	}
	ft_parent_process(av, env);
}
