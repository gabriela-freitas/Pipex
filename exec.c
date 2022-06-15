/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:04:05 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/15 16:43:05 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_command(char **command)
{
	int	i;

	ft_printf("comando : %s ", *command);
	i = 0;
	while (command[++i])
		ft_printf("%s ", command[i]);
	ft_printf("\n");
}

// pipe[0] >> read
// pipe[1] >> write

/*will allways read either from pipe_aux[0] or from infile
	and write on pipe_fd[1]*/
void	child_write_process(int fd_infile, char **command)
{
	print_command(command);
	if (fd_infile == -1)
	{
		close(infos()->pipe_aux[1]);
		if (dup2(infos()->pipe_aux[0], STDIN_FILENO) == -1)
			perror_and_exit("Could not dup second pipe[0]");
		close(infos()->pipe_aux[0]);
	}
	else
	{
		if (dup2(fd_infile, STDIN_FILENO) == -1)
			perror_and_exit("Could not dup infile");
	}
	// close(infos()->pipe_fd[0]);
	if (dup2(infos()->pipe_fd[1], STDOUT_FILENO) == -1)
		perror_and_exit("Could not dup pipe[1]");
	// close(infos()->pipe_fd[1]);
	execve(command[0], command, NULL);
	perror_and_exit("exec did not work");
}

/*will allways read pipe_fd[0]
	and write on pipe_aux[1] or outfile*/
void	child_read_process(int fd_outfile, char **command)
{
	print_command(command);
	if (fd_outfile == -1)
	{
		ft_putstr_fd(">>Hey\n", 2);
		close(infos()->pipe_aux[0]);
		if (dup2(infos()->pipe_aux[1], STDOUT_FILENO) == -1)
			perror_and_exit("Could not dup pipe");
		close(infos()->pipe_aux[1]);
	}
	else
	{
		if (dup2(fd_outfile, STDOUT_FILENO) < 0)
			perror_and_exit("Could not dup outfile");
	}
	close(STDIN_FILENO);
	// close(infos()->pipe_fd[1]);
	if (dup2(infos()->pipe_fd[0], STDIN_FILENO) == -1)
		perror_and_exit("Could not dup pipe");
	// close(infos()->pipe_fd[0]);
	ft_putstr_fd(">>Hey\n", 2);
	execve(command[0], command, NULL);
	perror_and_exit("exec did not work");
}
