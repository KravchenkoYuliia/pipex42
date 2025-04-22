/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:32:46 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/19 15:45:41 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_parent_process(int cmd_number, int ac, char **av, char **env)
{
	int	i;
	int	pipe_end[2];
	pid_t	pid;

	i = 1;
	while (i <= cmd_number)
	{
		pipe(pipe_end);
		pid = fork();
		if (pid == 0)
		{
			if (i + 1 == 2)
				ft_child_for_first_cmd(av[2], pipe_end, av,env);
			else if (i + 1 == ac - 2)
				ft_child_for_last_cmd(av[ac - 1], av[ac - 2], pipe_end, env);
			else
				ft_middle_child(av[i + 1], pipe_end, env);
		}
		dup2(pipe_end[0], STDIN_FILENO);
		i++;
		ft_close(-1, pipe_end);
	}
	while (waitpid(-1, NULL, 0) != -1)
		continue ;
}

void	ft_parent_with_heredoc()
{
	printf("Hey we start parent with heredoc\n");
}

void	ft_handle_heredoc(char **av)
{
	int	fd;
	int	diff;
	char *line;

	fd = open("heredoc",
                        O_RDWR | O_CREAT | O_TRUNC,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return ;
		diff = ft_strncmp(line, av[2], ft_strlen(line));
		if (diff == 0 || diff == '\n')
			break ;
		write(fd, line, ft_strlen(line));
	}
	close(fd);
}

void	ft_remove_limiter(int *ac, char **av)
{
	int i = 2;
	while (i < *ac)
	{
		av[i] = av[i + 1];
		i++;
	}

	*ac = *ac - 1;
}

int	main(int ac, char **av, char **env)
{
	int	cmd_number;

	if (ac < 5)
	{
		write(2, "not enough arguments\n", 21);
		exit(EXIT_FAILURE);
	}
	int is_heredoc;
	if (ft_strncmp(av[1], "heredoc", ft_strlen(av[1])) == 0)
	{
		is_heredoc = 1;
		ft_handle_heredoc(av);
		ft_remove_limiter(&ac, av);
	}
	else
		is_heredoc = 0;
	cmd_number = ac - 3;
	ft_parent_process(cmd_number, ac, av, env);

	if (is_heredoc)
		unlink("heredoc");
}
