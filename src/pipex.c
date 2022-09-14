/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:54:06 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/14 19:10:28 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	pipex(t_path *commands, int cmd_count, char **av, char **envp)
{
	int	i;
	int	fds[2];
	char buf;
	// int	*pipes;

	// fds[0] = 0;
	// fds[1] = open(av[cmd_count + 1], O_CREAT);
	// if (fds[0] < 0 || fds[1] < 0)
	// {
	// 	close(fds[0]);
	// 	close(fds[1]);
	// 	free_struct_and_exit(commands, cmd_count, "File opening failed\n");
	// }
	// pipes = malloc(cmd_count * sizeof(int));
	// if (!pipes)
	// 	free_struct_and_exit(commands, cmd_count, "Malloc failed\n");	
	if (pipe(fds) < 0)
		ft_print_exit("Pipe failed\n");
	commands[0].pid = fork();
	if (commands[0].pid == 0)
	{
		close(fds[1]);
		while (read(fds[0], &buf, 1) > 0)
			write(1, &buf, 1);
		write(1, "\n", 1);	
		close(fds[0]);
		exit(0);
	}
	else
	{
		close(fds[0]);
		write(fds[1], "TEST\n", 5);
		close(fds[1]);
		wait(NULL);
		exit(0);
	}

	i = 0;
	
	while (i < cmd_count)
	{
		commands[i].pid = fork();
		if (commands[i].pid < 0)
			free_struct_and_exit(commands, cmd_count, "Fork failed\n");
		else if (commands[i].pid > 0)
			waitpid(commands[i].pid, NULL, 0);
		else
			execve(commands[i].path, commands[i].args, envp);
		i++;
	}
}