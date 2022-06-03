/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/03 21:54:26 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**find_path(char **envp);

t_info	*infos(void)
{
	t_info	infos;

	return (&infos);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc || argv || envp)
	{
		infos()->paths = find_path(envp);
		infos()->infile = argv[1];
		infos()->cmd1 = ft_split(argv[2]);
		infos()->cmd2 = ft_split(argv[3]);
		infos()->outfile = argv[4];
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

/*find wich path is every command*/
static void	find_right_path(char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (infos()->paths[i])
	{
		cmd = ft_strjoin("/", cmd);
		path = ft_strjoin(infos()->paths[i], cmd);
		if (access(path, F_OK) == 0)
			break ;
		free(cmd);
		free(path);
		i ++;
	}
	free(cmd);
	return (path);
}
