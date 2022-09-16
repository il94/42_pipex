/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/16 19:55:09 by ilandols         ###   ########.fr       */
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

}	t_path;

/* pipex.c */
int		execute_command(t_path command, char **envp);
int		apply_dups(int new_stdin, int new_stdout);
int		redirect_flows(int *pipes, int *files, int i, int cmd_count);
void	pipex(t_path *commands, int cmd_count, char **av, char **envp);

/* get_paths.c */
char	*get_command_path(char *path, char **bin_paths);
char	**get_bin_paths(char **envp);
void	get_all_paths(t_path *commands, int cmd_count, char **av, char **envp);

/* free_memory.c */
void	free_pipes(int *pipes, int cmd_count);
void	free_fd(int *files);
void	free_files(int *files, int *pipes, int cmd_count);
void	free_struct(t_path *commands, int cmd_count);
void	free_struct_and_exit(t_path *commands, int cmd_count, char *str_error);

/* initialize.c */
int		*initalize_pipes(int cmd_count);
int		initialize_fd(char **av, int *files, int **pipes, int cmd_count);
void	initialize_command_with_args(t_path *commands, int i, char **av);
void	initialize_command_without_args(t_path *commands, int i, char **av);
t_path	*initialize_commands_struct(int cmd_count, char **av, char **envp);

/* main.c */
int		main(int ac, char **av, char **envp);

/* temp.c */
void	print_struct(t_path *commands, int size);

#endif
