/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:04:05 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/07 19:57:46 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_write_process(int fd_infile, char **command)
{
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		perror_and_exit("Could not dup infile");
	close(infos()->pipe_fd[0]);
	if (dup2(infos()->pipe_fd[1], STDOUT_FILENO) == -1)
		perror_and_exit("Could not dup pipe");
	close(infos()->pipe_fd[1]);
	execve(command[0], command, NULL);
	perror_and_exit("exec did not work");
}

void	child_read_process(int fd_outfile, char **command)
{
	close(infos()->pipe_fd[1]);
	if (dup2(infos()->pipe_fd[0], STDIN_FILENO) == -1)
		perror_and_exit("Could not dup pipe");
	close(infos()->pipe_fd[0]);
	if (fd_outfile == -1)
	{
		if (pipe(infos()->aux) == -1)
			perror_and_exit("Pipe didn't work");
		close(infos()->aux[1]);
		if (dup2(infos()->aux[0], STDOUT_FILENO) == -1)
			perror_and_exit("Could not dup pipe");
		close(infos()->aux[0]);
	}
	else
	{
		if (dup2(fd_outfile, STDOUT_FILENO) < 0)
			perror_and_exit("Could not dup outfile");
	}
	execve(command[0], command, NULL);
	perror_and_exit("exec did not work");
}
