/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:04:05 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/07 16:01:24 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_write_process(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		perror_and_exit("Could not dup");
	close(infos()->pipe_fd[0]);
	if (dup2(infos()->pipe_fd[1], 1) == -1)
		perror_and_exit("Could not dup");
	close(infos()->pipe_fd[1]);
	execve(infos()->cmd1[0], infos()->cmd1, NULL);
	perror_and_exit("exec did not work");
}

void	child_process2(void)
{
	int	fd;

	fd = infos()->fd_out;
	close(infos()->pipe_fd[1]);
	if (dup2(infos()->pipe_fd[0], 0) == -1)
		perror_and_exit("Could not dup");
	close(infos()->pipe_fd[0]);
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror_and_exit("Could not dup");
	execve(infos()->cmd2[0], infos()->cmd2, NULL);
	perror_and_exit("exec did not work");
}
