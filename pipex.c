/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/15 19:39:05 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_pipex(void);
static void	parent_process(int i);
static void	pipex(void);

int	main(int argc, char **argv, char **envp)
{
	if (argc > 4)
	{
		parse_argv(argc, argv, envp);
		pipex();
	}
	else
		perror_and_exit("Less than 5 args");
	return (0);
}

static void	pipex(void)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < infos()->num_cmds)
	{
		if (pipe(infos()->pipe_fd) == -1)
			perror_and_exit("Pipe didn't work");
		pid = fork();
		if (pid == -1)
			perror_and_exit("Could not fork");
		if (!pid)
			first_child_process(i);
		else
		{
			close(infos()->pipe_fd[1]);
			close(infos()->pipe_aux[0]);
			wait(NULL);
			i++;
			parent_process(i);
		}
	}
}

static void	parent_process(int i)
{
	pid_t	pid;

	if (pipe(infos()->pipe_aux) == -1)
		perror_and_exit("Pipe aux didn't work");
	pid = fork();
	if (pid == -1)
		perror_and_exit("Could not fork");
	if (!pid)
		second_child_process(i);
	else
	{
		close(infos()->pipe_fd[0]);
		close(infos()->pipe_aux[1]);
		wait(NULL);
		if (i == infos()->num_cmds - 1)
		{
			free_pipex();
			exit(EXIT_SUCCESS);
		}
	}
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
	int	i;

	free_split(infos()->paths);
	i = 0;
	while (i < infos()->num_cmds)
	{
		free_split(infos()->cmds[i]);
		i ++;
	}
	free_split(infos()->cmds[i]);
	close(infos()->fd_in);
	close(infos()->fd_out);
}
