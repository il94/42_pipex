/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:54:06 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/15 19:29:02 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	pipex(t_path *commands, int cmd_count, char **av, char **envp)
{
	int	i;
	char buf;
	int pid;
	int infile;
	int infile_dup;
	int outfile;
	int outfile_dup;
	// int *pipes;
	int pipes[2];
	
	infile = open(av[1], O_WRONLY);
	outfile = open(av[cmd_count + 2], O_WRONLY | O_CREAT);
	// pipes = malloc(cmd_count * 2 * sizeof(int));
	pipe(pipes);
	i = 0;
	// while (i < 2)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(infile, 0);
			dup2(pipes[1], 1);
			close(pipes[0]);
			execve(commands[i].path, &commands[i].path, envp);
			
		}
		else
		{
			// close(pipes[1]);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
		pid = fork();
		if (pid == 0)
		{
			dup2(pipes[0], 0);
			dup2(outfile, 1);
			close(pipes[0]);
			execve(commands[i].path, &commands[i].path, envp);
			
		}
		else
		{
			// close(pipes[1]);
			waitpid(pid, NULL, 0);
		}





	
	// i = 0;
	// while (i < cmd_count)
	// {
	// 	commands[i].pid = fork();
	// 	if (commands[i].pid < 0)
	// 		free_struct_and_exit(commands, cmd_count, "Fork failed\n");
	// 	else if (commands[i].pid > 0)
	// 		waitpid(commands[i].pid, NULL, 0);
	// 	else
	// 	{
	// 		if (commands[i].args)
	// 			execve(commands[i].path, commands[i].args, envp);
	// 		else
	// 			execve(commands[i].path, &commands[i].path, envp);
	// 	}
	// 	i++;
	// }
}