/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:18:48 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/04 14:22:18 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*returns the struct with infos*/
t_info	*infos(void)
{
	static t_info	info;

	return (&info);
}

/*get env variable PATH and split it*/
char	**find_path(char **envp)
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
int	find_right_path(char **cmd)
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
