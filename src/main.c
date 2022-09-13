/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:52:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/13 20:31:22 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd	*commands;
	int		cmd_count;
	char	*cmd1;
	char	*cmd2;

	if (ac < 5)
		ft_print_exit("Not enough arguments\n");
	if (!envp[0])
		ft_print_exit("Env is not registred\n");
	cmd_count = ac - 3;
	commands = initialize_commands_struct(cmd_count, av, envp);
	get_all_paths(commands, cmd_count, av, envp);
	print_struct(commands, cmd_count);
	free_commands_struct(commands, cmd_count);
	return (0);
}
