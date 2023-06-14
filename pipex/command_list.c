/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_command(t_commands *new, t_pipex *list)
{
	t_commands	*tmp;

	tmp = list->commands;
	if (!list->commands)
	{
		list->commands = new;
		return ;
	}
	while (tmp->next != 0)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

void	new_commands(t_commands *com, t_pipex *list)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	new->next = 0;
	new->redin = com->redin;
	new->redout = com->redout;
	new->args = com->args;
	new->filein = com->filein;
	new->fileout = com->fileout;
	new->builtin = com->builtin;
	add_command(new, list);
}

void	free_commands(t_pipex *pipex)
{
	t_commands	*com;
	t_commands	*tmp;

	com = pipex->commands;
	tmp = pipex->commands;
	while (com != 0)
	{
		free(com->args);
		com = tmp->next;
		free(tmp);
		tmp = com;
	}
	pipex->commands = 0;
}
