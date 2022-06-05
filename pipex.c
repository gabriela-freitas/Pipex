/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/05 20:22:42 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid[2];

	if (argc == 5)
	{
		parse_argv(argv, envp);
		if (pipe(infos()->pipe_fd) == -1)
			perror("Pipe didn't work");
		pid[0] = fork();
		if (!pid[0])
			child_write_process(infos()->fd_in);
		else
		{
			wait(&pid[0]);
			pid[1] = fork();
			if (!pid[1])
				child_process2();
			else
				return (0);
		}
	}
	return (0);
}
