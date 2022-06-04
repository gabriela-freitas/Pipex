/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/04 13:58:14 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**find_path(char **envp);
static int	find_right_path(char **cmd);

t_info	*infos(void)
{
	static t_info	info;

	return (&info);
}

int	main(int argc, char **argv, char **envp)
{
	int fd, fd1;

	if (argc || argv || envp)
	{
		infos()->paths = find_path(envp);
		infos()->infile = argv[1];
		infos()->cmd1 = ft_split(argv[2], ' ');
		// infos()->cmd2 = ft_split(argv[3], ' ');
		// infos()->outfile = argv[4];
		// find_right_path(&(infos()->cmd2[0]));
		find_right_path(&(infos()->cmd1[0]));
		fd = open(infos()->infile, O_RDONLY | O_ASYNC);
		dup2(fd, 0);
		fd1 = open("outfile", O_RDWR | O_CREAT | O_ASYNC);
		dup2(fd1, 1);
		execve(infos()->cmd1[0], infos()->cmd1, envp);
	}
	else
		return (0);
}

/*get env variable PATH and split it*/
static char	**find_path(char **envp)
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
static int	find_right_path(char **cmd)
{
	char	*path;
	int		i;
	char	*aux;

	i = 0;
	while (infos()->paths[i])
	{
		aux = ft_strjoin("/", *cmd);
		path = ft_strjoin(infos()->paths[i], aux);
		free(aux);
		if (access(path, F_OK) == 0)
		{
			*cmd = path;
			ft_printf("cmd: %s\n", *cmd);
			return (1);
		}
		free(path);
		i ++;
	}
	return (0);
}
