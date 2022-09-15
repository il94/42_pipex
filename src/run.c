/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:15:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/15 15:05:47 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_struct_and_exit(t_path *commands, int cmd_count, char *str_error)
{
	free_struct(commands, cmd_count);
	if (str_error)
		ft_print_exit(str_error);
	exit (1);
}

void	free_struct(t_path *commands, int cmd_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd_count)
	{
		if (commands[i].args)
		{
			j = 0;
			while (commands[i].args[j])
			{
				if (commands[i].args[j])
					free(commands[i].args[j]);
				j++;
			}
			free(commands[i].args);
		}
		if (commands[i].path)
			free(commands[i].path);
		i++;
	}
	free(commands);
}

void	initialize_command_with_args(t_path *commands, int i, char **av)
{
	char	*args_list;

	args_list = ft_strdup(av[i + 2]);
	if (!args_list)
		free_struct_and_exit(commands, i, "Malloc failed\n");
	commands[i].path = ft_strcut_left(av[i + 2], ' ');
	commands[i].args = ft_split(args_list, ' ');
	if (!commands[i].path && !commands[i].args)
	{
		free(args_list);
		free_struct_and_exit(commands, i, "Malloc failed\n");
	}
	free(args_list);
}

void	initialize_command_without_args(t_path *commands, int i, char **av)
{
	commands[i].path = ft_strdup(av[i + 2]);
	commands[i].args = NULL;
	if (!commands[i].path)
		free_struct_and_exit(commands, i, "Malloc failed\n");
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
