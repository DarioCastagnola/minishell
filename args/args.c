/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_args(t_args *arg, t_pipex *pipex)
{
	t_args	*tmp;

	tmp = pipex->args;
	while (tmp)
	{
		if (ft_strcmp_args(arg->key, tmp->key) == 0)
		{
			tmp->value = arg->value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	compact_unset_args(t_pipex *pipex, t_args *tmp)
{
	pipex->args = pipex->args->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	compact_unset_args2(t_args *tmp, t_args *prev)
{
	prev->next = tmp->next;
	free(tmp->value);
	free(tmp->key);
	free(tmp);
}

void	unset_args(char *key, t_pipex *pipex)
{
	t_args	*tmp;
	t_args	*prev;

	if (exist_ambient_var(key, pipex) == 1)
	{
		unset_ambient(key, pipex);
		return ;
	}
	tmp = pipex->args;
	prev = tmp;
	if (tmp && ft_strcmp_args(tmp->key, key) == 0)
	{
		compact_unset_args(pipex, tmp);
		return ;
	}
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		if (tmp && ft_strcmp_args(tmp->key, key) == 0)
		{
			compact_unset_args2(tmp, prev);
			return ;
		}
	}	
}
