/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:40:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/22 18:27:06 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	print_struct(t_path *commands, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		printf("[%d] path = %s\n", i, commands[i].path);
		if (commands[i].args)
		{
			j = 0;
			while (commands[i].args[j])
			{
				printf("[%d][%d] = %s\n", i, j, commands[i].args[j]);
				j++;
			}
		}
		i++;
		printf("==================\n");
	}
}

void	print_fd(t_fds fd_list, int size)
{
	int	i;

	printf("[0] files = %d\n", fd_list.files[0]);
	printf("[1] files = %d\n", fd_list.files[1]);
	i = 0;
	while (i < size * 2)
	{
		printf("[%d] pipes = %d\n", i, fd_list.pipes[i]);
		i++;
	}
	printf("==================\n");
}
