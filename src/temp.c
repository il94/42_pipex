/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:40:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/14 11:59:12 by ilandols         ###   ########.fr       */
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
