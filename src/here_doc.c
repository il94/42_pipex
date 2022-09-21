/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:57:03 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/22 00:11:05 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	generate_here_doc(char **av, t_fds *fd_list, int cmd_count)
{
	char	*buffer;
	
	buffer = NULL;
	fd_list->limiter = ft_strdup(av[2]);
	if (!fd_list->limiter)
	{
		ft_printf("Malloc failed\n");
		return ;	
	}
	fd_list->files[0] = open(av[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	fd_list->files[1] = open(av[cmd_count + 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (1)
	{
		ft_printf("heredoc> ");
		buffer = ft_get_next_line(0);
		if (!ft_strncmp(fd_list->limiter, buffer, ft_strlen(fd_list->limiter)))
			break ;
		write(fd_list->files[0], buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	free(fd_list->limiter);
}
