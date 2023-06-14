/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->path[i])
	{
		free(pipex->path[i]);
		i++;
	}
	free(pipex->path);
}

void	child_free(t_commands *com)
{
	int	i;

	i = 0;
	while (com->cmd_args[i])
	{
		free(com->cmd_args[i]);
		i++;
	}
	free(com->cmd_args);
	free(com->command);
}

void	free_total(t_pipex *pipex)
{
	free_envp(pipex);
	free_path(pipex);
	close(pipex->stdin);
	close(pipex->stdout);
	free_args(pipex);
}

void	free_mat(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
	mat = 0;
}
