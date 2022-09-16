/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:52:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/16 17:20:50 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_path	*commands;
	int		cmd_count;

	if (ac < 5)
		ft_print_exit("Not enough arguments\n");
	if (!envp[0])
		ft_print_exit("Env is not registred\n");
	cmd_count = ac - 3;
	commands = initialize_commands_struct(cmd_count, av, envp);
	get_all_paths(commands, cmd_count, av, envp);
	pipex(commands, cmd_count, av, envp);
	free_struct(commands, cmd_count);
	return (0);
}
