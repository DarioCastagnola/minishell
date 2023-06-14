/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_args(t_pipex *pipex)
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
	int	i;

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

void	add_ordered(t_args *new, t_pipex *pipex)
{
	t_args	*tmp;

	tmp = pipex->args;
	while (tmp)
	{
		if (ft_strcmp_args(new->key, tmp->key) <= 0
			&& (tmp->next == 0
				|| ft_strcmp_args(new->key, tmp->next->key) >= 0))
		{
			new->next = tmp->next;
			tmp->next = new;
			return ;
		}
		tmp = tmp->next;
	}
	new->next = pipex->args;
	pipex->args = new;
}

void	add_arg(t_args *arg, t_pipex *pipex)
{
	t_args	*new;

	unset_args(arg->key, pipex);
	if (check_args(arg, pipex))
		return ;
	new = malloc(sizeof(t_args));
	new->key = arg->key;
	new->value = arg->value;
	if (!pipex->args)
	{
		new->next = 0;
		pipex->args = new;
		return ;
	}
	add_ordered(new, pipex);
}
