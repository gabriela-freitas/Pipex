/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:45:13 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/02 23:15:59 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**find_path(char **envp);

int main	(int argc, char **argv, char **envp)
{
	if (argc || argv || envp)
	{
		find_path(envp);
	}
	else
		return (0);
}

static char	**find_path(char **envp)
{
	char	**path;
	char	*aux;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
		{
			aux = *envp;
			break ;
		}
		envp++;
	}
	aux = ft_strchr(aux, '=');
	ft_printf("%s", aux);
	path = ft_split(aux, ':');
	while (*path)
	{
		ft_printf("%s\n", *path);
		path ++;
	}
	free_split(path);
	return (0);
}
