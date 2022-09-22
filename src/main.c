/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:52:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/22 19:43:35 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_path	*commands;

	if (ac >= 6 && ft_strcmp(av[1], "here_doc\0") == 0)
		commands = initialize_commands_struct(ac - 4, av + 3);
	else if (ac >= 5 && ft_strcmp(av[1], "here_doc\0") != 0)
		commands = initialize_commands_struct(ac - 3, av + 2);
	else
		ft_print_exit("Not enough arguments\n");
	printf("cmd_count = %d\n", commands->cmd_count);
	if (envp[0])
		get_all_paths(commands, av, envp);
	print_struct(commands, 2);
	pipex(commands, av, envp);
	free_struct(commands, commands->cmd_count);
	return (0);
}
