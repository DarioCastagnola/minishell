/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exist_ambient_var(char *key, t_pipex *pipex)
{
	int		i;

	i = 0;
	while (pipex->envp[i])
	{
		if (ft_strncmp(key, pipex->envp[i], ft_strlen(key)) == 0)
			break ;
		i++;
	}
	if (pipex->envp[i] == 0)
		return (-1);
	return (1);
}

int	find_ambient_var(char *key, t_pipex *pipex)
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

void	unset_ambient(char *key, t_pipex *pipex)
{
	int		i;
	char	*tmp;

	i = find_ambient_var(key, pipex);
	free(pipex->envp[i]);
	tmp = ft_strjoin(key, "=");
	pipex->envp[i] = tmp;
}

void	set_ambient(char *key, char *value, t_pipex *pipex)
{
	int		i;
	char	*tmp;
	char	*def;

	i = find_ambient_var(key, pipex);
	tmp = ft_strjoin(key, "=");
	def = ft_strjoin(tmp, value);
	free(tmp);
	free(pipex->envp[i]);
	pipex->envp[i] = def;
}
