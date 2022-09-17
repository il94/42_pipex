/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:23:40 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/17 12:29:51 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_all_and_exit(t_fds *fd_list, t_path *commands, char *str_error)
{
	free_files(fd_list, commands->cmd_count);
	free_struct_and_exit(commands, commands->cmd_count, str_error);
}

void	free_files(t_fds *fd_list, int cmd_count)
{
	int	i;

	if (fd_list->files[0] > -1)
		close(fd_list->files[0]);
	if (fd_list->files[1] > -1)
		close(fd_list->files[1]);
	if (fd_list->pipes)
	{
		i = 0;
		while (i < cmd_count)
		{
			if (fd_list->pipes[i] > -1)
				close(fd_list->pipes[i]);
			i++;
		}
		free(fd_list->pipes);
	}
}

void	free_struct(t_path *commands, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (commands[i].args)
			ft_free_array(commands[i].args);
		if (commands[i].path)
			free(commands[i].path);
		i++;
	}
	free(commands);
}

void	free_struct_and_exit(t_path *commands, int cmd_count, char *str_error)
{
	free_struct(commands, cmd_count);
	if (str_error)
		ft_print_exit(str_error);
	exit (1);
}
