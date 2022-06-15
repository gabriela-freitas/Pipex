/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/15 20:14:47 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(void);
void	exit_message(char *error);

int	main(int argc, char **argv, char **envp)
{
	if (argc > 4)
	{
		parse_argv(argc, argv, envp);
		pipex();
	}
	else
		exit_message("Less than 5 args");
	return (0);
}

void	exit_message(char *error)
{
	perror(error);
	free_pipex();
	exit(EXIT_FAILURE);
}

void	free_pipex(void)
{
	int	i;

	free_split(infos()->paths);
	if (infos()->cmds)
	{
		i = 0;
		while (i < infos()->num_cmds)
		{
			free_split(infos()->cmds[i]);
			i ++;
		}
		free_split(infos()->cmds[i]);
	}
	if (infos()->fd_in)
		close(infos()->fd_in);
	if (infos()->fd_out)
		close(infos()->fd_out);
}
