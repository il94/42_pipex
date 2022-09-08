/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:52:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/08 19:31:13 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


int	main(int ac, char **av, char **envp)
{
	// if (ac < 5)
	// 	ft_print_exit("Invalid input\n");
	// if (ft_strcmp(av[1], "here_doc"))
	int	i = 0;

	char	 *envp_path;
	char 	*result;
	char	**paths;

	while (envp[i] && !envp_path)
	{
		envp_path = ft_strnstr(envp[i], "PATH", 4);
		i++;
	}
	printf("%s\n", envp_path);
	// ft_strlcpy(result, envp[i], ft_strlen(envp[i]));
	// printf("\n%s\n", result);
	// paths = ft_split(result, ':');
	// i = 0;
	// while (paths[i])
	// {
	// 	printf("%s\n", paths[i]);
	// 	i++;
	// }
	// execve("/usr/bin/ls", av, envp);
		
	
	// int	fd3;
	// int	fd4;

	// int	fd5;
	// int fd6;

	// int	fd7;
	// int fd8;
	
	// fd3 = open("test/infile", O_RDONLY);
	// fd4 = open("test/outfile", O_RDONLY);
	// fd5 = dup(fd3);
	// fd6 = dup(fd4);
	// fd7 = dup(fd5);
	// fd8 = dup(fd6);
	
	// printf("fd3 = %d | fd4 = %d | fd5 = %d | fd6 = %d | fd7 = %d | fd8 = %d\n", fd3, fd4, fd5, fd6, fd7, fd8);
	// printf("%d\n", access("./pipex", 2));
	return (0);
}
