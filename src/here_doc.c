/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:57:03 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/24 19:20:00 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	opening_fd_here_doc(t_cmds *cmd_list, t_fds *fd_list, char **av)
{
	fd_list->files[0] = open("/tmp/.heredoc", O_RDWR | O_EXCL | O_CREAT, 0644);
	if (fd_list->files[0] == -1)
	{
		printf("TEST INPUT\n");
		free_struct_and_exit(cmd_list, cmd_list->cmd_count, "open");
	}
	fd_list->files[1] = open(av[cmd_list->cmd_count + 3],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_list->files[1] == -1)
	{
		printf("TEST OUTPUT\n");
		free_all_and_exit(fd_list, cmd_list, "open");
	}
}

void	writing_here_doc(t_cmds *cmd_list, t_fds *fd_list, char **av)
{
	char	*buffer;

	buffer = NULL;
	fd_list->limiter = ft_strdup(av[2]);
	if (!fd_list->limiter)
		free_struct_and_exit(cmd_list, cmd_list->cmd_count, "malloc");
	while (1)
	{
		ft_printf("heredoc> ");
		buffer = ft_get_next_line(STDIN_FILENO);
		if (!buffer)
			free_all_and_exit(fd_list, cmd_list, "malloc");
		if (!ft_strncmp(fd_list->limiter, buffer, ft_strlen(fd_list->limiter)))
			break ;
		write(fd_list->files[0], buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd_list->files[0]);
}

void	generate_here_doc(t_cmds *cmd_list, t_fds *fd_list, char **av)
{
	fd_list->limiter = NULL;
	opening_fd_here_doc(cmd_list, fd_list, av);
	writing_here_doc(cmd_list, fd_list, av);
}
