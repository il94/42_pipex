/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:11:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/03 12:48:55 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_command_path(char *path, char **bin_paths)
{
	char	*command_path;
	int		i;

	i = 0;
	while (!ft_strchr(path, '/') && ft_strlen(path) > 0 && bin_paths[i])
	{
		command_path = ft_pathjoin(bin_paths[i], path);
		if (!command_path)
		{
			free(path);
			perror("malloc");
			return (NULL);
		}
		if (access(command_path, X_OK) == 0)
		{
			free(path);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	return (path);
}

char	**get_bin_paths(char **envp)
{
	char	**bin_paths;
	char	*read_line;
	int		i;

	i = 0;
	bin_paths = NULL;
	read_line = NULL;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (envp[i])
	{
		read_line = ft_strnstr(envp[i], "PATH", 4);
		bin_paths = ft_split(&read_line[5], ':');
		if (!bin_paths)
		{
			perror("malloc");
			return (NULL);
		}
	}
	return (bin_paths);
}

void	get_all_paths(t_cmds *cmd_list, char **envp)
{
	char	**bin_paths;
	int		i;

	bin_paths = get_bin_paths(envp);
	if (!bin_paths)
		free_struct_and_exit(cmd_list, cmd_list->cmd_count, NULL);
	i = 0;
	while (i < cmd_list->cmd_count)
	{
		cmd_list[i].path = get_command_path(cmd_list[i].path, bin_paths);
		if (!cmd_list[i].path)
		{
			ft_free_array(bin_paths);
			free_struct_and_exit(cmd_list, cmd_list->cmd_count, NULL);
		}
		i++;
	}
	ft_free_array(bin_paths);
}
