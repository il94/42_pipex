/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:53:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/13 20:10:06 by ilandols         ###   ########.fr       */
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
void	get_all_paths(t_cmd *commands, int commands_count, char **av, char **envp);

/* main.c */
void	free_commands_struct(t_cmd *commands, int commands_count);
t_cmd	*initialize_commands_struct(int *commands_count, int ac, char **av, char **envp);
int		main(int ac, char **av, char **envp);

/* temp.c */
void	print_struct(t_cmd *commands, int size);

#endif
