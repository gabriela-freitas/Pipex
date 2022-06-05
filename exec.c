/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:04:05 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/05 20:23:44 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_write_process(int fd)
{
	ft_printf("Im the child\n");
	// fd = open(infos()->infile, O_RDONLY | O_ASYNC);
	// if (fd < 0)
	// 	perror("cannot open file\n");
	dup2(fd, 0);
	close(infos()->pipe_fd[0]);
	dup2(infos()->pipe_fd[1], 1);
	close(infos()->pipe_fd[1]);
	execve(infos()->cmd1[0], infos()->cmd1, NULL);
	printf("something wrong happen\n");
}

void	child_process2(void)
{
	int	fd;

	fd = infos()->fd_out;
	ft_printf("Im the child2\n");
	close(infos()->pipe_fd[1]);
	dup2(infos()->pipe_fd[0], 0);
	close(infos()->pipe_fd[0]);
	// fd = open(infos()->outfile, O_WRONLY | O_ASYNC | O_CREAT, S_IRWXU);
	// if (fd < 0)
	// 	perror("cannot open file\n");
	if (dup2(fd, 1) < 0)
		perror("cannot dup\n");
	execve(infos()->cmd2[0], infos()->cmd2, NULL);
	printf("something wrong happen\n");
}
