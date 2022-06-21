/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:55:55 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/21 21:23:04 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	parent_process(int i);

void	pipex(void)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < infos()->num_cmds)
	{
		if (pipe(infos()->pipe_fd) == -1)
			exit_message("Pipe didn't work");
		pid = fork();
		if (pid == -1)
			exit_message("Could not fork");
		if (!pid)
			first_child_process(i);
		else
		{
			close(infos()->pipe_fd[1]);
			close(infos()->pipe_aux[0]);
			wait(NULL);
			i++;
			if (parent_process(i))
				break ;
		}
	}
	free_pipex();
	exit(EXIT_SUCCESS);
}

/*execute first fork's parent process*/
static int	parent_process(int i)
{
	pid_t	pid;

	if (pipe(infos()->pipe_aux) == -1)
		exit_message("Pipe aux didn't work");
	pid = fork();
	if (pid == -1)
		exit_message("Could not fork");
	if (!pid)
		second_child_process(i);
	else
	{
		close(infos()->pipe_fd[0]);
		close(infos()->pipe_aux[1]);
		wait(NULL);
		if (i == infos()->num_cmds - 1)
			return (1);
	}
	return (0);
}
