/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:47:17 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/05 20:22:19 by gafreita         ###   ########.fr       */
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
	char	**cmd1;
	char	**cmd2;
	int		pipe_fd[2];
	int		fd_out;
	int		fd_in;
}	t_info;


t_info		*infos(void);
void		parse_argv(char **argv, char **envp);
void		child_write_process(int fd);
void		child_process2(void);
#endif
