/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:54:06 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/18 19:54:53 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	apply_dups(int new_stdin, int new_stdout)
{
	int	fd1;
	int	fd2;

	fd1 = dup2(new_stdin, 0);
	fd2 = dup2(new_stdout, 1);
	if (fd1 == -1 || fd2 == -1)
		return (0);
	return (1);
}

int	redirect_flows(t_fds *fd_list, int i, int cmd_count)
{
	// if (fd_list->files[i] == -1)
	// {
	// 		return (0);
	// }
	if (i == 0)
	{
		if (!apply_dups(fd_list->files[0], fd_list->pipes[i + 1]))
			return (0);
	}
	else if (i == cmd_count - 1)
	{
		if (!apply_dups(fd_list->pipes[i * 2 - 2], fd_list->files[1]))
			return (0);
	}	
	else
	{
		if (!apply_dups(fd_list->pipes[i * 2 - 2], fd_list->pipes[i * 2 + 1]))
			return (0);
	}
	close(fd_list->pipes[i * 2]);
	return (1);
}

void	child_process(t_fds *fd_list, t_path *commands, int i, char **envp)
{
	printf("CHILD\n");
	// if (fd_list->files[i] == -1)
	// {
	// 	free_all_and_exit(fd_list, commands, "TEST\n");
	// }
	// else
	{
		if (!redirect_flows(fd_list, i, commands->cmd_count))
			free_all_and_exit(fd_list, commands, "Dup Failed\n");
		if (commands[i].args)
			execve(commands[i].path, commands[i].args, envp);
		else
			execve(commands[i].path, &commands[i].path, envp);
	}
}

void	parent_process(t_fds *fd_list, pid_t pid, int i)
{
	close(fd_list->pipes[i * 2 + 1]);
	waitpid(pid, NULL, 0);
}

void	pipex(t_path *commands, char **av, char **envp)
{
	int		i;
	pid_t	pid;
	t_fds	fd_list;

	if (!initialize_fd(av, &fd_list, commands->cmd_count))
		free_struct_and_exit(commands, commands->cmd_count, NULL);
	i = 0;
	// if (fd_list.files[0] == -1)
	// 	i++;
	while (i < commands->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			free_all_and_exit(&fd_list, commands, "Fork failed\n");
		else if (pid == 0)
			child_process(&fd_list, commands, i, envp);
		else
			parent_process(&fd_list, pid, i);
		i++;
	}
	free_files(&fd_list, commands->cmd_count);
}
