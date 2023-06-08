/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/06/08 15:34:20 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_path(t_pipex *pipex, char *key)
{
	int		i;

	i = 0;
	while (pipex->envp[i])
	{
		if (ft_strncmp(key, pipex->envp[i], ft_strlen(key)) == 0)
			break ;
		i++;
	}
	return (i);
}

void	unset_pat(t_pipex *pipex, char *key)
{
		int		i;

		i = find_path(pipex, key);
		free(pipex->envp[i]);
}

void	set_path(char *s, t_pipex *pipex)
{
		int		i;
		char	*tmp;

		i = find_path(pipex, s);
		tmp = ft_strjoin(pipex->envp[i], s);
		free(pipex->envp[i]);
		pipex->envp[i] = tmp;
}
