/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:15:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/24 22:31:08 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	is_valid_input(int ac, char **av)
{
	int	i;

	i = 0;
	if ((av[1] && ac < 6 && ft_strcmp(av[1], "here_doc\0") == 0) || ac < 5)
		return (0);
	while (i < ac)
	{
		if (ft_strlen(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	initalize_pipes(t_cmds *cmd_list, t_fds *fd_list)
{
	int	i;

	fd_list->pipes = malloc(cmd_list->cmd_count * 2 * sizeof(int));
	if (!fd_list->pipes)
		free_all_and_exit(fd_list, cmd_list, "malloc");
	i = 0;
	while (i < cmd_list->cmd_count)
		fd_list->pipes[i++] = -1;
	i = 0;
	while (i < cmd_list->cmd_count && pipe(&fd_list->pipes[i * 2]) == 0)
		i++;
	if (i < cmd_list->cmd_count)
		free_all_and_exit(fd_list, cmd_list, "pipe");
}

void	initialize_fd(t_cmds *cmd_list, t_fds *fd_list, char **av)
{
	fd_list->files[0] = -1;
	fd_list->files[1] = -1;
	fd_list->limiter = NULL;
	fd_list->pipes = NULL;
	if (ft_strcmp(av[1], "here_doc\0") == 0)
	{
		generate_here_doc(cmd_list, fd_list, av);
		fd_list->files[0] = open("/tmp/.heredoc", O_RDONLY, 0644);
	}
	else
	{
		fd_list->files[1] = open(av[cmd_list->cmd_count + 2],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_list->files[1] == -1)
			free_all_and_exit(fd_list, cmd_list, "open");
		fd_list->files[0] = open(av[1], O_RDONLY);
	}
	if (fd_list->files[0] == -1)
		perror("open");
	initalize_pipes(cmd_list, fd_list);
}

void	initialize_command(t_cmds *cmd_list, int i, char *av)
{
	char	*args_list;

	args_list = ft_strdup(av);
	if (!args_list)
		free_struct_and_exit(cmd_list, i, "malloc");
	cmd_list[i].path = ft_strcut_left(av, ' ');
	cmd_list[i].args = ft_split(args_list, ' ');
	if (!cmd_list[i].path || !cmd_list[i].args)
	{
		free(args_list);
		free_struct_and_exit(cmd_list, i + 1, "malloc");
	}
	free(args_list);
}

t_cmds	*initialize_cmd_list_struct(int cmd_count, char **args)
{
	t_cmds	*cmd_list;
	int		i;

	cmd_list = malloc(cmd_count * sizeof(t_cmds));
	if (!cmd_list)
		ft_perror_exit("malloc");
	cmd_list->cmd_count = cmd_count;
	i = 0;
	while (i < cmd_count)
	{
		initialize_command(cmd_list, i, args[i]);
		i++;
	}
	return (cmd_list);
}
