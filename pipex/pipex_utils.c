/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	path(t_pipex *pipex)
{
	int		i;

	i = 0;
	while (pipex->envp[i])
	{
		if (ft_strncmp("PATH", pipex->envp[i], 4) == 0)
			break ;
		i++;
	}
	pipex->path = ft_split(pipex->envp[i] + 5, ':');
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (0);
}

void	save_io(t_pipex *pipex)
{
	pipex->stdin = dup(0);
	pipex->stdout = dup(1);
}

void	cmd_trim(char **mat)
{
	int		i;
	char	*tmp;

	i = -1;
	while (mat[++i])
	{
		if (mat[i] == 0)
			continue ;
		if (mat[i][0] == '"')
		{
			tmp = ft_strtrim(mat[i], "\"");
			free(mat[i]);
			mat[i] = tmp;
		}
		if (mat[i][0] == '\'')
		{
			tmp = ft_strtrim(mat[i], "'");
			free(mat[i]);
			mat[i] = tmp;
		}
	}
}

char	*trim_red(char *s)
{
	char	*tmp;

	if (s[0] == '"')
	{
		tmp = ft_strtrim(s, "\"");
		free(s);
		return (tmp);
	}
	if (s[0] == '\'')
	{
		tmp = ft_strtrim(s, "'");
		free(s);
		return (tmp);
	}
	return (s);
}
