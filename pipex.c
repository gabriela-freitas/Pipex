/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/07 20:17:04 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_pipex(void);
static int	parent_process(void);

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid[2];
	int		i;

	if (argc == 5)
	{
		parse_argv(argv, envp);
		if (pipe(infos()->pipe_fd) == -1)
			perror_and_exit("Pipe didn't work");
		i = -1;
		while (1)
		{
			pid[0] = fork();
			if (pid[0] == -1)
				perror_and_exit("Could not fork");
			if (!pid[0])
				child_write_process(infos()->fd_in, infos()->cmds[i]);
			else
			{
				i++;
				wait(&pid[0]);
				if (parent_process(i))
					return (0);
			}

		}
	}
	return (0);
}

static void	parent_process(int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror_and_exit("Could not fork");
	if (!pid)
	{
		child_process2();

	}
	else
		free_pipex();
	return ;
}

void	perror_and_exit(char *error)
{
	perror(error);
	free_pipex();
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
