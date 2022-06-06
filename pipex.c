/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/06 20:27:56 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_pipex(void);
static int	parent_process(void);

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid[2];

	if (argc == 5)
	{
		parse_argv(argv, envp);
		if (pipe(infos()->pipe_fd) == -1)
			perror_and_exit("Pipe didn't work\n");
		pid[0] = fork();
		if (pid[0] == -1)
			perror_and_exit("Could not fork\n");
		if (!pid[0])
			child_write_process(infos()->fd_in);
		else
		{
			wait(&pid[0]);
			if (parent_process())
				return (0);
		}
	}
	return (0);
}

static int	parent_process(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror_and_exit("Could not fork\n");
	if (!pid)
		child_process2();
	else
		free_pipex();
	return (1);
}

void	perror_and_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

static void	free_pipex(void)
{
	free_split(infos()->paths);
	free_split(infos()->cmd1);
	free_split(infos()->cmd2);
	close(infos()->fd_in);
	close(infos()->fd_out);
}
