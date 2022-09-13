/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:40:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/13 19:47:25 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	print_struct(t_cmd *commands, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf ("[%d] cmd = %s | arg = %s\n", i, commands[i].cmd, commands[i].arg);
		i++;
	}
}
