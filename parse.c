/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:18:48 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/05 18:19:08 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_info		*infos(void);
static char	**get_path(char **envp);
static int	get_command_path(char **cmd);

/*parse agrs*/
void	parse_argv(char **argv, char **envp)
{
	infos()->paths = get_path(envp);
	(infos())->fd_in = open(argv[1], O_RDONLY | O_ASYNC);
	if ((infos())->fd_in)
		perror("cannot open input file\n");
	(infos())->cmd1 = ft_split(argv[2], ' ');
	(infos())->cmd2 = ft_split(argv[3], ' ');
	(infos())->fd_out = open(argv[4], O_WRONLY | O_ASYNC | O_CREAT, S_IRWXU);
	if ((infos())->fd_out < 0)
		perror("cannot open file\n");
	get_command_path(&(infos()->cmd2[0]));
	get_command_path(&(infos()->cmd1[0]));
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
static int	get_command_path(char **cmd)
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
			*cmd = path;
			free(aux);
			ft_printf("cmd: %s\n", *cmd);
			return (1);
		}
		free(path);
		i ++;
	}
	free(aux);
	return (0);
}
