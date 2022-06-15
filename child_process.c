/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:04:05 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/15 20:14:47 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_command(int read, int write, char **command);
void		first_child_process(int i);
void		second_child_process(int i);

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
/*execute command with execve*/
static void	exec_command(int read, int write, char **command)
{
	print_command(command);
	if (dup2(read, STDIN_FILENO) == -1)
		exit_message("could not dup read fd");
	if (dup2(write, STDOUT_FILENO) == -1)
		exit_message("could not dup output fd");
	execve(command[0], command, NULL);
	exit_message("exec did not work");
}

/* write process ::: will allways read either from pipe_aux[0] or from infile
	and write on pipe_fd[1]*/
void	first_child_process(int i)
{
	if (i == 0)
		exec_command(infos()->fd_in, infos()->pipe_fd[1], infos()->cmds[i]);
	else if (i == infos()->num_cmds - 1)
		exec_command(infos()->pipe_aux[0], infos()->fd_out, infos()->cmds[i]);
	else
		exec_command(infos()->pipe_aux[0],
			infos()->pipe_fd[1], infos()->cmds[i]);
}

/*read process ::: will allways read pipe_fd[0]
	and write on pipe_aux[1] or outfile*/
void	second_child_process(int i)
{
	if (i == infos()->num_cmds - 1)
		exec_command(infos()->pipe_fd[0], infos()->fd_out, infos()->cmds[i]);
	else
		exec_command(infos()->pipe_fd[0],
			infos()->pipe_aux[1], infos()->cmds[i]);
}
