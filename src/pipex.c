/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:54:06 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/03 12:49:43 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	dup_fd(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FILENO) == -1
		|| dup2(new_stdout, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

int	redirect_flows(t_fds *fd_list, int i, int cmd_count)
{
	if (i == 0)
		return (dup_fd(fd_list->files[0], fd_list->pipes[i + 1]));
	else if (i == cmd_count - 1)
		return (dup_fd(fd_list->pipes[i * 2 - 2], fd_list->files[1]));
	else
		return (dup_fd(fd_list->pipes[i * 2 - 2], fd_list->pipes[i * 2 + 1]));
}

void	child_process(t_cmds *cmd_list, t_fds *fd_list, int i, char **envp)
{
	if (access(cmd_list[i].path, X_OK) == -1)
		free_all_and_exit(fd_list, cmd_list, "access");
	if (!redirect_flows(fd_list, i, cmd_list->cmd_count))
		free_all_and_exit(fd_list, cmd_list, NULL);
	free_files(fd_list, cmd_list->cmd_count, 0);
	execve(cmd_list[i].path, cmd_list[i].args, envp);
}

void	pipex(t_cmds *cmd_list, t_fds *fd_list, char **envp)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < cmd_list->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			free_all_and_exit(fd_list, cmd_list, "fork");
		else if (pid == 0)
			child_process(cmd_list, fd_list, i, envp);
		else if (i > 0)
			close(fd_list->pipes[i * 2 - 2]);
		close(fd_list->pipes[i * 2 + 1]);
		i++;
	}
	i = 0;
	while (i < cmd_list->cmd_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	if (access("/tmp/.heredoc", F_OK) == 0)
		unlink("/tmp/.heredoc");
}
