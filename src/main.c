/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:52:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/12 19:23:03 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_command_path(char *cmd, char **bin_paths)
{
	char	*command_path;
	int		i;

	i = 0;
	command_path = ft_pathjoin(bin_paths[i], cmd);
	if (!command_path)
		ft_print_exit("Malloc failed\n");
	while (bin_paths[i] && access(command_path, X_OK) < 0)
	{
		free(command_path);
		i++;
		if (!bin_paths[i])
			ft_print_exit("Path not found\n");
		command_path = ft_pathjoin(bin_paths[i], cmd);
		if (!command_path)
			ft_print_exit("Malloc failed\n");
	}
	printf("command_path = %s\n", command_path);
	return (command_path);
}

int	main(int ac, char **av, char **envp)
{
	// if (ft_strcmp(av[1], "here_doc"))
	char	**bin_paths;
	char	*cmd1;
	char	*cmd2;

	// if (ac < 5)
	// 	ft_print_exit("Invalid input\n");
	bin_paths = get_bin_paths(envp);
	cmd1 = get_command_path(av[2], bin_paths);
	cmd2 = get_command_path(av[3], bin_paths);
	// ft_print_array(bin_paths);
	ft_free_array(bin_paths);
	free(cmd1);
	free(cmd2);
	// execve("/usr/bin/ls", av, envp);
	return (0);
}
