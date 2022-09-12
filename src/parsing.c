/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:11:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/12 18:59:35 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_bin_paths(char **envp)
{
	char	**bin_paths;
	char	 *read_line;
	int		i;

	i = 0;
	read_line = NULL;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
	{
		i++;
		if (!envp[i])
			ft_print_exit("Env variable PATH is not registred\n");
	}
	read_line = ft_strnstr(envp[i], "PATH", 4);
	bin_paths = ft_split(&read_line[5], ':');
	if (!bin_paths)
		ft_print_exit("Malloc failed\n");
	return (bin_paths);
}

int	is_valid_input(int ac, char **av)
{
	if (ac < 5)
		return (0);
}