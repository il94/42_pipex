/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:54:06 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/22 21:31:37 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	apply_dups(int new_stdin, int new_stdout)
{
	if (dup2(new_stdin, STDIN_FILENO) == -1
		|| dup2(new_stdout, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

int	redirect_flows(t_fds *fd_list, int i, int cmd_count)
{
	if (i == 0)
		return (apply_dups(fd_list->files[0], fd_list->pipes[i + 1]));
	else if (i == cmd_count - 1)
		return (apply_dups(fd_list->pipes[i * 2 - 2], fd_list->files[1]));
	else
		return (apply_dups(fd_list->pipes[i * 2 - 2], fd_list->pipes[i * 2 + 1]));
}

void	child_process(t_fds *fd_list, t_path *commands, int i, char **envp)
{
	if (access(commands[i].path, X_OK) != 0)
		free_all_and_exit(fd_list, commands, "Command not found\n");		
	if (!redirect_flows(fd_list, i, commands->cmd_count))
		free_all_and_exit(fd_list, commands, "Dup Failed\n");
	close(fd_list->pipes[i * 2]);
	execve(commands[i].path, commands[i].args, envp);
}

void	pipex(t_path *commands, char **av, char **envp)
{
	int		i;
	pid_t	pid;
	t_fds	fd_list;

	// printf("outfile = %s\n", av[commands->cmd_count + 3]);
	if (!initialize_fd(av, &fd_list, commands->cmd_count))
		free_struct_and_exit(commands, commands->cmd_count, NULL);
	// print_struct(commands, 2);
	print_fd(fd_list, 2);
	i = 0;
	while (i < commands->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			free_all_and_exit(&fd_list, commands, "Fork failed\n");
		else if (pid == 0)
			child_process(&fd_list, commands, i, envp);
		else
			close(fd_list.pipes[i * 2 + 1]);
		i++;
	}
	waitpid(pid, NULL, 0);
	free_files(&fd_list, commands->cmd_count);
	unlink("here_doc");
}
