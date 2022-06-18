/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:35:59 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/18 21:57:02 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_here_doc(int argc, char **argv, char **envp);

void	here_doc(int argc, char **argv, char **envp)
{
	char	*c;

	parse_here_doc(argc, argv, envp);
	while (1)
	{
		read(0, &c, 1);
		c = get_next_line(1);
		write(1, "hey\n", 4);
		if (!ft_strncmp(c, argv[2], ft_strlen(c) + 1))
			break ;
		write(infos()->fd_in, &c, 1);
	}
	//unlink(TEMP_FILE);
}

void	parse_here_doc(int argc, char **argv, char **envp)
{
	infos()->cmds = NULL;
	infos()->paths = get_path(envp);
	(infos())->fd_in = open(TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC | O_ASYNC, 0644);
	if ((infos())->fd_in < 0)
		exit_message("cannot open input file");
	(infos())->fd_out = open(argv[argc - 1], O_WRONLY | O_ASYNC
			| O_APPEND | O_CREAT, S_IRWXU);
	if ((infos())->fd_out < 0)
		exit_message("cannot create output file");
	infos()->num_cmds = argc - 4;
	parse_commands(argc - 2, &argv[2]);
}
