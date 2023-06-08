/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    print_args(t_pipex *pipex)
{
	t_args	*tmp;

	tmp = pipex->args;
	while (tmp)
	{
		if (ft_strcmp_args(tmp->key, "?"))
		{
			printf("%s=%s\n", tmp->key, tmp->value);
		}	
		tmp = tmp->next;
	}
}

int	ft_strcmp_args(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	free_args(t_pipex *pipex)
{
	t_args	*tmp;

	while (pipex->args != 0)
	{
		tmp = pipex->args->next;
		free(pipex->args->key);
		free(pipex->args->value);
		free(pipex->args);
		pipex->args = tmp;
	}
}

char	*get_var(char *key, t_pipex *pipex)
{
	t_args *tmp;

	if (!key)
		return (0);
	tmp = pipex->args;
	while (tmp)
	{
		if (ft_strcmp_args(key, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (0);
}