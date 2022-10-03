/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:23:40 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/26 13:54:44 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_files(t_fds *fd_list, int cmd_count, t_bool array)
{
	int	i;

	if (fd_list->files[0] > -1)
		close(fd_list->files[0]);
	if (fd_list->files[1] > -1)
		close(fd_list->files[1]);
	if (fd_list->pipes)
	{
		i = 0;
		while (i < cmd_count * 2)
		{
			if (fd_list->pipes[i] > -1)
				close(fd_list->pipes[i]);
			i++;
		}
		if (array)
			free(fd_list->pipes);
	}
}

void	free_struct(t_cmds *cmd_list, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (cmd_list[i].args)
			ft_free_array(cmd_list[i].args);
		if (cmd_list[i].path)
			free(cmd_list[i].path);
		i++;
	}
	free(cmd_list);
}

void	free_struct_and_exit(t_cmds *cmd_list, int cmd_count, char *str_error)
{
	free_struct(cmd_list, cmd_count);
	if (str_error)
		ft_perror_exit(str_error);
	exit (1);
}

void	free_all_and_exit(t_fds *fd_list, t_cmds *cmd_list, char *str_error)
{
	free_files(fd_list, cmd_list->cmd_count, 1);
	free_struct_and_exit(cmd_list, cmd_list->cmd_count, str_error);
}
