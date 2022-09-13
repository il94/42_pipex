/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:11:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/13 20:09:58 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char *get_command_path(char *cmd, char **bin_paths)
{
	char	*command_path;
	int		i;

	i = 0;
	while (bin_paths[i])
	{
		command_path = ft_pathjoin(bin_paths[i], cmd);
		if (!command_path)
		{
			ft_printf("Malloc failed\n");
			return (NULL);
		}
		if (access(command_path, X_OK) >= 0)
		{
			free(cmd);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free(cmd);
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

void	get_all_paths(t_cmd *commands, int commands_count, char **av, char **envp)
{
	char	**bin_paths;
	int		i;

	bin_paths = get_bin_paths(envp);
	if (!bin_paths)
	{
		free_commands_struct(commands, commands_count);
		exit (1);
	}
	i = 0;
	while (i < commands_count)
	{
		commands[i].cmd = get_command_path(commands[i].cmd, bin_paths);
		if (!commands[i].cmd)
		{
			ft_free_array(bin_paths);
			free_commands_struct(commands, commands_count);
			exit (1);
		}
		i++;
	}
	ft_free_array(bin_paths);
}
