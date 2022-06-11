/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/11 21:22:50 by gafreita         ###   ########.fr       */
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
		parse_argv(argc, argv, envp);
		i = 0;
		while (1)
		{
			if (pipe(infos()->pipe_fd) == -1)
				perror_and_exit("Pipe didn't work");
			pid = fork();
			if (pid == -1)
				perror_and_exit("Could not fork");
			if (!pid)
			{
				write(1, "Hey\n", 4);
				ft_printf("i = %d\n", i);
				if (i == 0)
					child_write_process(infos()->fd_in, infos()->cmds[i]);
				else
					child_write_process(-1, infos()->cmds[i]);
			}
			else
			{
				i++;
				wait(&pid);
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

	if (pipe(infos()->pipe_aux) == -1)
		perror_and_exit("Pipe aux didn't work");
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
