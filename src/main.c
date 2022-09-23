/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:52:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/23 18:19:03 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_cmds	*cmd_list;
	t_fds	fd_list;

	if (ac >= 6 && ft_strcmp(av[1], "here_doc\0") == 0)
		cmd_list = initialize_cmd_list_struct(ac - 4, av + 3);
	else if (ac >= 5 && ft_strcmp(av[1], "here_doc\0") != 0)
		cmd_list = initialize_cmd_list_struct(ac - 3, av + 2);
	else
		ft_print_exit("Not enough arguments\n");
	if (envp[0])
		get_all_paths(cmd_list, envp);
	initialize_fd(cmd_list, &fd_list, av);
	pipex(cmd_list, &fd_list, envp);
	free_files(&fd_list, cmd_list->cmd_count);
	free_struct(cmd_list, cmd_list->cmd_count);
	return (0);
}
