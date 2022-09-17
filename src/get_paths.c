/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:11:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/17 17:44:50 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_command_path(char *path, char **bin_paths)
{
	char	*command_path;
	int		i;

	i = 0;
	while (bin_paths[i])
	{
		command_path = ft_pathjoin(bin_paths[i], path);
		if (!command_path)
		{
			free(path);
			ft_printf("Malloc failed\n");
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
	free(path);
	ft_printf("Command not found\n");
	return (NULL);
}

char	**get_bin_paths(char **envp)
{
	char	**bin_paths;
	char	*read_line;
	int		i;

	i = 0;
	read_line = NULL;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
	{
		i++;
		if (!envp[i])
		{
			ft_printf("Env variable PATH is not registred\n");
			return (NULL);
		}
	}
	read_line = ft_strnstr(envp[i], "PATH", 4);
	bin_paths = ft_split(&read_line[5], ':');
	if (!bin_paths)
	{
		ft_printf("Malloc failed\n");
		return (NULL);
	}
	return (bin_paths);
}

void	get_all_paths(t_path *commands, char **av, char **envp)
{
	char	**bin_paths;
	int		i;

	bin_paths = get_bin_paths(envp);
	if (!bin_paths)
		free_struct_and_exit(commands, commands->cmd_count, NULL);
	i = 0;
	while (i < commands->cmd_count)
	{
		if (access(commands[i].path, X_OK) == -1)
			commands[i].path = get_command_path(commands[i].path, bin_paths);
		if (!commands[i].path)
		{
			ft_free_array(bin_paths);
			free_struct_and_exit(commands, commands->cmd_count, NULL);
		}
		i++;
	}
	ft_free_array(bin_paths);
}
