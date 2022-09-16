/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:23:40 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/16 19:36:44 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_pipes(int *pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (pipes[i] > -1)
			close(pipes[i]);
		i++;
	}
	free(pipes);
}

void	free_fd(int *files)
{
	if (files[0] > -1)
		close(files[0]);
	if (files[1] > -1)
		close(files[1]);
}

void	free_files(int *files, int *pipes, int cmd_count)
{
	if (files[0] > -1 || files[1] > -1)
		free_fd(files);
	if (pipes)
		free_pipes(pipes, cmd_count);
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
