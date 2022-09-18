/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:15:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/18 19:02:48 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	initalize_pipes(t_fds *fd_list, int cmd_count)
{
	int	i;

	fd_list->pipes = malloc(cmd_count * 2 * sizeof(int));
	if (!fd_list->pipes)
	{
		ft_printf("Malloc failed\n");
		return (0);
	}
	i = 0;
	while (i < cmd_count && pipe(&fd_list->pipes[i * 2]) == 0)
		i++;
	if (i < cmd_count)
	{
		ft_printf("Failed opening file\n");
		free_files(fd_list, i);
		return (0);
	}
	return (1);
}

int	initialize_fd(char **av, t_fds *fd_list, int cmd_count)
{
	fd_list->pipes = NULL;
	if (!ft_strcmp(av[1], "here_doc\0"))
		generate_here_doc(av, fd_list);
	else	
		fd_list->files[0] = open(av[1], O_RDONLY);
	fd_list->files[1] = open(av[cmd_count + 2], O_WRONLY | O_CREAT, 0644);
	if (fd_list->files[0] == -1)
		ft_printf("Failed opening infile\n");
	if (fd_list->files[1] == -1)
	{
		ft_printf("Failed opening outfile\n");
		free_files(fd_list, cmd_count);
		return (0);
	}
	if (!initalize_pipes(fd_list, cmd_count))
	{
		ft_printf("Failed opening file\n");
		free_files(fd_list, cmd_count);
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

t_path	*initialize_commands_struct(int ac, char **av, char **envp)
{
	t_path	*commands;
	int		i;
	int		cmd_count;

	cmd_count = ac - 3;
	commands = malloc(cmd_count * sizeof(t_path));
	if (!commands)
		ft_print_exit("Malloc failed\n");
	commands->cmd_count = cmd_count;
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
