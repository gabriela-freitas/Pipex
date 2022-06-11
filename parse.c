/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:18:48 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/11 21:18:18 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_info		*infos(void);
static char	**get_path(char **envp);
static void	get_command_path(char **cmd);
static void	parse_commands(int argc, char **argv);

/*parse agrs*/
void	parse_argv(int argc, char **argv, char **envp)
{
	infos()->paths = get_path(envp);
	(infos())->fd_in = open(argv[1], O_RDONLY | O_ASYNC);
	if ((infos())->fd_in < 0)
		perror_and_exit("cannot open input file");
	(infos())->fd_out = open(argv[argc - 1], O_WRONLY | O_ASYNC
			| O_TRUNC | O_CREAT, S_IRWXU);
	if ((infos())->fd_out < 0)
		perror_and_exit("cannot create output file");
	infos()->num_cmds = argc - 3;
	parse_commands(argc, argv);
}

/*parse every command and find path*/
static void	parse_commands(int argc, char **argv)
{
	int	i;

	(infos())->cmds = malloc(sizeof(char *) * (argc - 2));
	i = 0;
	while ((i + 2) < argc - 1)
	{
		(infos()->cmds)[i] = ft_split(argv[i + 2], ' ');
		get_command_path((infos()->cmds)[i]);
		i ++;
	}
	infos()->cmds[i] = NULL;
}

/*returns the struct with infos*/
t_info	*infos(void)
{
	static t_info	info;

	return (&info);
}

/*get env variable PATH and split it*/
static char	**get_path(char **envp)
{
	char	**path;
	char	*aux;

	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	aux = ft_strchr(*envp, '=') + 1;
	path = ft_split(aux, ':');
	return (path);
}

/*find in which path is every command*/
static void	get_command_path(char **cmd)
{
	char	*path;
	int		i;
	char	*aux;

	i = 0;
	aux = ft_strjoin("/", *cmd);
	while (infos()->paths[i])
	{
		path = ft_strjoin(infos()->paths[i], aux);
		if (access(path, F_OK) == 0)
		{
			free(*cmd);
			*cmd = path;
			free(aux);
			return ;
		}
		free(path);
		i ++;
	}
	free(aux);
	if (access(path, F_OK) == -1)
		perror_and_exit("Not a valid command or path");
	return ;
}
