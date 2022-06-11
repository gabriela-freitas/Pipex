/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:47:17 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/11 21:17:14 by gafreita         ###   ########.fr       */
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

typedef struct s_info
{
	char	**paths;
	char	***cmds;
	int		pipe_fd[2];
	int		pipe_aux[2];
	int		fd_out;
	int		fd_in;
	int		num_cmds;
}	t_info;

t_info		*infos(void);
void		parse_argv(int argc, char **argv, char **envp);
void		child_write_process(int fd_infile, char **command);
void		child_read_process(int fd_outfile, char **command);
void		perror_and_exit(char *error);

#endif
