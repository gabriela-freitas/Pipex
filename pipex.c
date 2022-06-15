/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/13 20:52:28 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_pipex(void);
static void	parent_process(int i);

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		i;

	if (argc > 4)
	{
		(infos())->fd_fake = open("pseudo_pipe", O_RDWR | O_ASYNC | O_TRUNC);
		parse_argv(argc, argv, envp);
		ft_printf("n de cmds: %d\n", infos()->num_cmds);
		i = 0;
		while (1)
		{
			// if (pipe(infos()->pipe_fd) == -1)
			// 	perror_and_exit("Pipe didn't work");
			pid = fork();
			if (pid == -1)
				perror_and_exit("Could not fork");
			if (!pid)
			{
				ft_printf("i = %d\npipe fd[0] = %d\n", i, infos()->pipe_fd[1]);
				if (i == 0)
					child_write_process(infos()->fd_in, infos()->cmds[i]);
				else
					child_write_process(-1, infos()->cmds[i]);
			}
			else
			{
				wait(NULL);
				i++;
				ft_printf("i = %d(parent)\n", i);
				parent_process(i);
			}
		}
	}
	else
		perror_and_exit("Less than 5 args");
	return (0);
}

static void	parent_process(int i)
{
	pid_t	pid;

	// if (pipe(infos()->pipe_aux) == -1)
	// 	perror_and_exit("Pipe aux didn't work");
	pid = fork();
	if (pid == -1)
		perror_and_exit("Could not fork");
	if (!pid)
	{
		if (i == infos()->num_cmds - 1)
			child_read_process(infos()->fd_out, infos()->cmds[i]);
		else
			child_read_process(-1, infos()->cmds[i]);
	}
	else
	{
		wait(&pid);
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
	close(infos()->fd_in);
	close(infos()->fd_out);
}
