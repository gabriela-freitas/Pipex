/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/04 16:49:20 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int fd, fd1, pid;
	int pipe_fd[2];

	if (argc || argv || envp)
	{
		infos()->paths = find_path(envp);
		infos()->infile = argv[1];
		infos()->cmd1 = ft_split(argv[2], ' ');
		infos()->cmd2 = ft_split(argv[3], ' ');
		infos()->outfile = argv[4];
		find_right_path(&(infos()->cmd2[0]));
		find_right_path(&(infos()->cmd1[0]));
		pid = fork();
		if (pipe(pipe_fd) == -1)
			perror("Pipe didn't work");
		if (!pid)
		{
			ft_printf("Im the child\n");
			fd = open(infos()->infile, O_RDONLY | O_ASYNC);
			if (fd < 0)
				perror("cannot open file\n");
			dup2(fd, 0);
			dup2(pipe_fd[1], 1);
			execve(infos()->cmd1[0], infos()->cmd1, envp);
			printf("something wrong happen\n");
		}
		else
		{
			wait(&pid);
			ft_printf("I've waited\n");
			dup2(pipe_fd[0], 0);
			fd1 = open("outfile", O_WRONLY | O_ASYNC);
			if (fd1 < 0)
				perror("cannot open file\n");
			if (dup2(fd1, 1) < 0)
				perror("cannot dup\n");
			ft_printf("heyy\nheyy");
			// execve(infos()->cmd2[0], infos()->cmd2, envp);
		}
	}
	else
		return (0);
}
