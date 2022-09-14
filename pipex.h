/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/14 18:07:20 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_path
{
	char	*path;
	char	**args;
	pid_t	pid;

}	t_path;

/* pipex.c */
void	pipex(t_path *commands, int cmd_count, char **av, char **envp);

/* parsing.c */
char	*get_command_path(char *path, char **bin_paths);
char	**get_bin_paths(char **envp);
void	get_all_paths(t_path *commands, int cmd_count, char **av, char **envp);

/* utils.c */
void	free_struct_and_exit(t_path *commands, int cmd_count, char *str_error);
void	free_struct(t_path *commands, int cmd_count);
void	initialize_command_with_args(t_path *commands, int i, char **av);
void	initialize_command_without_args(t_path *commands, int i, char **av);
t_path	*initialize_commands_struct(int cmd_count, char **av, char **envp);

/* main.c */
int		main(int ac, char **av, char **envp);

/* temp.c */
void	print_struct(t_path *commands, int size);

#endif
