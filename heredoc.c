/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:35:59 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/19 17:50:34 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_here_doc(int argc, char **argv, char **envp);

void	here_doc(int argc, char **argv, char **envp)
{
	char	*line;
	int		fd;

	//line = malloc(sizeof(char) * BUFFER_SIZE);
	parse_here_doc(argc, argv, envp);
	fd = open("infile", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		write(2, "hey!\n", 5);
		if (!line)
			break ;
		// ft_printf(">> %s\n", line);
		free(line);
	}
	close(fd);
	// while (1)
	// {
	// 	line = get_next_line(fd);
	// 	if (!ft_strncmp(line, argv[2], ft_strlen(line) + 1))
	// 		break ;
	// 	ft_printf("line >> %s\n", line);
	// 	write(infos()->fd_in, line, ft_strlen(line));
	// }
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
