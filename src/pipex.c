/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:54:06 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/16 19:57:58 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	execute_command(t_path command, char **envp)
{
	if (command.args)
		execve(command.path, command.args, envp);
	else
		execve(command.path, &command.path, envp);
}

int	apply_dups(int new_stdin, int new_stdout)
{
	int	fd1;
	int	fd2;

	fd1 = dup2(new_stdin, 0);
	fd2 = dup2(new_stdout, 1);
	if (fd1 == -1 || fd2 == -1)
	{
		return (0);
	}
	return (1);
}

int	redirect_flows(int *pipes, int *files, int i, int cmd_count)
{
	if (i == 0)
	{
		if (!apply_dups(files[0], pipes[i + 1]))
			return (0);
	}
	else if (i == cmd_count - 1)
	{
		if (!apply_dups(pipes[i * 2 - 2], files[1]))
			return (0);
	}	
	else
	{
		if (!apply_dups(pipes[i * 2 - 2], pipes[i * 2 + 1]))
			return (0);
	}
	close(pipes[i * 2]);
	return (1);
}

void	pipex(t_path *commands, int cmd_count, char **av, char **envp)
{
	int	i;
	int	pid;
	int	files[2];
	int	*pipes;

	if (!initialize_fd(av, files, &pipes, cmd_count))
		free_struct_and_exit(commands, cmd_count, NULL);
	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == -1)
		{
			free_files(files, pipes, cmd_count);
			free_struct_and_exit(commands, cmd_count, "Fork failed\n");
		}
		else if (pid == 0)
		{
			if (!redirect_flows(pipes, files, i, cmd_count))
			{
				free_files(files, pipes, cmd_count);
				free_struct_and_exit(commands, cmd_count, "Dup Failed\n");
			}
			execute_command(commands[i], envp);
		}
		else
		{
			close(pipes[i * 2 + 1]);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	free_files(files, pipes, cmd_count);
}
