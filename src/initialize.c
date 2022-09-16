/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:15:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/16 19:36:28 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	*initalize_pipes(int cmd_count)
{
	int	*pipes;
	int	i;

	pipes = malloc(cmd_count * 2 * sizeof(int));
	if (!pipes)
	{
		ft_printf("Malloc failed\n");
		return (NULL);
	}
	i = 0;
	while (i < cmd_count && pipe(&pipes[i * 2]) == 0)
		i++;
	if (i < cmd_count)
	{
		ft_printf("Failed opening file\n");
		free_pipes(pipes, i);
		return (NULL);
	}
	return (pipes);
}

int	initialize_fd(char **av, int *files, int **pipes, int cmd_count)
{
	*pipes = NULL;
	files[0] = open(av[1], O_RDONLY);
	files[1] = open(av[cmd_count + 2], O_WRONLY | O_CREAT);
	if (files[0] == -1 || files[1] == -1)
	{
		ft_printf("Failed opening file\n");
		free_fd(files);
		return (0);
	}
	*pipes = initalize_pipes(cmd_count);
	if (!*pipes)
	{
		ft_printf("Failed opening file\n");
		free_fd(files);
		return (0);
	}
	return (1);
}

void	initialize_command_with_args(t_path *commands, int i, char **av)
{
	char	*args_list;

	args_list = ft_strdup(av[i + 2]);
	if (!args_list)
		free_struct_and_exit(commands, i, "Malloc failed\n");
	commands[i].path = ft_strcut_left(av[i + 2], ' ');
	commands[i].args = ft_split(args_list, ' ');
	if (!commands[i].path || !commands[i].args)
	{
		free(args_list);
		free_struct_and_exit(commands, i + 1, "Malloc failed\n");
	}
	free(args_list);
}

void	initialize_command_without_args(t_path *commands, int i, char **av)
{
	commands[i].path = ft_strdup(av[i + 2]);
	commands[i].args = NULL;
	if (!commands[i].path)
		free_struct_and_exit(commands, i + 1, "Malloc failed\n");
}

t_path	*initialize_commands_struct(int cmd_count, char **av, char **envp)
{
	t_path	*commands;
	int		i;

	commands = malloc(cmd_count * sizeof(t_path));
	if (!commands)
		ft_print_exit("Malloc failed\n");
	i = 0;
	while (i < cmd_count)
	{
		if (ft_strchr(av[i + 2], ' '))
			initialize_command_with_args(commands, i, av);
		else
			initialize_command_without_args(commands, i, av);
		i++;
	}
	return (commands);
}
