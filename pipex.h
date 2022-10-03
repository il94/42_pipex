/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/03 12:41:29 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_cmds
{
	int		cmd_count;
	char	*path;
	char	**args;

}	t_cmds;

typedef struct s_fds
{
	int		files[2];
	int		*pipes;
	char	*here_doc_name;

}	t_fds;

/* here_doc.c */
void	opening_fd_here_doc(t_cmds *cmd_list, t_fds *fd_list, char **av);
void	writing_here_doc(t_cmds *cmd_list, t_fds *fd_list, char **av);
void	generate_here_doc(t_cmds *cmd_list, t_fds *fd_list, char **av);

/* pipex.c */
int		dup_fd(int new_stdin, int new_stdout);
int		redirect_flows(t_fds *fd_list, int i, int cmd_count);
void	child_process(t_cmds *cmd_list, t_fds *fd_list, int i, char **envp);
void	pipex(t_cmds *cmd_list, t_fds *fd_list, char **envp);

/* get_paths.c */
char	*get_command_path(char *path, char **bin_paths);
char	**get_bin_paths(char **envp);
void	get_all_paths(t_cmds *cmd_list, char **envp);

/* free_memory.c */
void	free_files(t_fds *fd_list, int cmd_count, t_bool array);
void	free_struct(t_cmds *cmd_list, int cmd_count);
void	free_struct_and_exit(t_cmds *cmd_list, int cmd_count, char *str_error);
void	free_all_and_exit(t_fds *fd_list, t_cmds *cmd_list, char *str_error);

/* initialize.c */
void	initalize_pipes(t_cmds *cmd_list, t_fds *fd_list);
void	initialize_fd(t_cmds *cmd_list, t_fds *fd_list, char **av);
void	initialize_command(t_cmds *cmd_list, int i, char *av);
t_cmds	*initialize_cmd_list_struct(int cmd_count, char **args);

/* main.c */
int		main(int ac, char **av, char **envp);

#endif
