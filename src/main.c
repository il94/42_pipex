/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:52:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/20 18:57:26 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_path	*commands;

	if (ac < 5)
		ft_print_exit("Not enough arguments\n");
	// if (!envp[0])
	// 	ft_print_exit("Env is not registred\n");
	commands = initialize_commands_struct(ac, av, envp);
	get_all_paths(commands, av, envp);
	pipex(commands, av, envp);
	free_struct(commands, commands->cmd_count);
	return (0);
}
