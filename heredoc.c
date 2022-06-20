/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:35:59 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/20 22:15:38 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_here_doc(int argc, char **argv, char **envp);

void	here_doc(int argc, char **argv, char **envp)
{
	char	*line;
	char	**aux;

	parse_here_doc(argc, argv, envp);
	while (1)
	{
		ft_printf("pipex heredoc> ");
		line = get_next_line(STDIN_FILENO);
		aux = ft_split(line, '\n');
		if (!ft_strncmp(*aux, argv[2], ft_strlen(line) + 1))
		{
			free_split(aux);
			free(line);
			break ;
		}
		free_split(aux);
		write(infos()->fd_in, line, ft_strlen(line));
		free(line);
	}
	close(infos()->fd_in);
	(infos())->fd_in = open(TEMP_FILE, O_RDONLY | O_ASYNC);
	if ((infos())->fd_in < 0)
		exit_message("cannot open .temp file");
}

void	parse_here_doc(int argc, char **argv, char **envp)
{
	infos()->envp = envp;
	infos()->cmds = NULL;
	infos()->paths = get_path(envp);
	(infos())->fd_in = open(TEMP_FILE, O_WRONLY | O_CREAT
			| O_ASYNC, 0644);
	if ((infos())->fd_in < 0)
		exit_message("cannot open input file");
	(infos())->fd_out = open(argv[argc - 1], O_WRONLY | O_ASYNC
			| O_APPEND | O_CREAT, S_IRWXU);
	if ((infos())->fd_out < 0)
		exit_message("cannot create output file");
	infos()->num_cmds = argc - 4;
	parse_commands(argc - 1, &argv[1]);
}
