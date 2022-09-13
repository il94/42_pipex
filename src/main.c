/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:52:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/13 20:09:32 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_commands_struct(t_cmd *commands, int commands_count)
{
	int	i;

	i = 0;
	while (i < commands_count)
	{
		if (commands[i].cmd)
			free(commands[i].cmd);
		if (commands[i].arg)
			free(commands[i].arg);
		i++;
	}
	free(commands);
}

t_cmd	*initialize_commands_struct(int *commands_count, int ac, char **av, char **envp)
{
	t_cmd	*commands;
	int	i;

	*commands_count = ac - 3;
	commands = malloc(*commands_count * sizeof(t_cmd));
	if (!commands)
		ft_print_exit("Malloc failed\n");
	i = 0;
	while (i < *commands_count)
	{
		if (ft_strchr(av[i + 2], ' '))
		{
			commands[i].cmd = ft_strcut_left(av[i + 2], ' ');
			commands[i].arg = ft_strcut_right(av[i + 2], ' ');
			if (!commands[i].cmd || !commands[i].arg)
				free_commands_struct(commands, *commands_count);
		}
		else
		{
			commands[i].cmd = ft_strdup(av[i + 2]);
			commands[i].arg = NULL;
			if (!commands[i].cmd)
				free_commands_struct(commands, *commands_count);
		}
		i++;
	}
	return (commands);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*commands;
	int		commands_count;
	char	*cmd1;
	char	*cmd2;

	// ft_print_array(envp);
	if (ac < 5)
		ft_print_exit("Not enough arguments\n");
	if (!envp[0])
		ft_print_exit("Env is not registred\n");
	commands = initialize_commands_struct(&commands_count, ac, av, envp);
	get_all_paths(commands, commands_count, av, envp);
	print_struct(commands, commands_count);
	free_commands_struct(commands, commands_count);
	// execve(cmd1, av, envp);
	return (0);
}
