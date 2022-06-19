/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:47:17 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/19 16:22:03 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# define TEMP_FILE "./.temp"

typedef struct s_info
{
	char	**paths;
	char	***cmds;
	char	**envp;
	int		pipe_fd[2];
	int		pipe_aux[2];
	int		fd_out;
	int		fd_in;
	int		num_cmds;
}	t_info;

t_info		*infos(void);
void		parse_argv(int argc, char **argv, char **envp);
char		**get_path(char **envp);
void		get_command_path(char **cmd);
void		parse_commands(int argc, char **argv);
void		exit_message(char *error);
void		first_child_process(int i);
void		second_child_process(int i);
void		pipex(void);
void		free_pipex(void);
void		here_doc(int argc, char **argv, char **envp);

#endif
