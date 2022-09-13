/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/13 20:31:22 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_cmd
{
	char	*cmd;
	char	*arg;

}	t_cmd;

/* parsing.c */
char	*get_command_path(char *cmd, char **bin_paths);
char	**get_bin_paths(char **envp);
void	get_all_paths(t_cmd *commands, int cmd_count, char **av, char **envp);

/* utils.c */
void	free_commands_struct(t_cmd *commands, int cmd_count);
void	initialize_command_with_arg(t_cmd *commands, int i, char **av);
void	initialize_command_without_arg(t_cmd *commands, int i, char **av);
t_cmd	*initialize_commands_struct(int cmd_count, char **av, char **envp);

/* main.c */
int		main(int ac, char **av, char **envp);

/* temp.c */
void	print_struct(t_cmd *commands, int size);

#endif
