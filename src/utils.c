/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:15:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/13 20:31:22 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_commands_struct(t_cmd *commands, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (commands[i].cmd)
			free(commands[i].cmd);
		if (commands[i].arg)
			free(commands[i].arg);
		i++;
	}
	free(commands);
}

void	initialize_command_with_arg(t_cmd *commands, int i, char **av)
{
	commands[i].cmd = ft_strcut_left(av[i + 2], ' ');
	commands[i].arg = ft_strcut_right(av[i + 2], ' ');
	if (!commands[i].cmd || !commands[i].arg)
		free_commands_struct(commands, i);
}

void	initialize_command_without_arg(t_cmd *commands, int i, char **av)
{
	commands[i].cmd = ft_strdup(av[i + 2]);
	commands[i].arg = NULL;
	if (!commands[i].cmd)
		free_commands_struct(commands, i);
}

t_cmd	*initialize_commands_struct(int cmd_count, char **av, char **envp)
{
	t_cmd	*commands;
	int		i;

	commands = malloc(cmd_count * sizeof(t_cmd));
	if (!commands)
		ft_print_exit("Malloc failed\n");
	i = 0;
	while (i < cmd_count)
	{
		if (ft_strchr(av[i + 2], ' '))
			initialize_command_with_arg(commands, i, av);
		else
			initialize_command_without_arg(commands, i, av);
		i++;
	}
	return (commands);
}
