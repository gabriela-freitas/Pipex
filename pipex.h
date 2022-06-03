/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:47:17 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/03 21:40:44 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include "libft.h"

typedef struct s_info
{
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
}	t_info;

#endif
