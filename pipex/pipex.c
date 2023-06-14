/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	compact_exe(int *tmp, t_commands *wp, t_pipex *pipex)
{
	wait_process(tmp, wp);
	close_red(pipex);
	if (pipex->commands)
		free_commands(pipex);
}

void	compact_exe2(t_commands *commands, t_pipex *pipex, int *fd, int *tmp)
{
	if (!commands->pid)
	{
		ft_signal();
		exec(pipex, tmp, fd, commands);
	}
	if (commands->pid)
	{
		ft_signal();
		close_parent(tmp, fd);
	}
}

void	compact_exe3(t_pipex *pipex, int *fd, int *tmp)
{
	*tmp = fd[0];
	dup2(pipex->stdin, 0);
	dup2(pipex->stdout, 1);
}

void	reset_sig(void)
{
	ft_reset_signal();
	sigaction(SIGINT, 0, 0);
	sigaction(SIGQUIT, 0, 0);
}

void	exe(t_pipex *pipex)
{
	int			tmp;
	int			fd[2];
	t_commands	*commands;

	if (!pipex->commands)
		return ;
	create_red(pipex);
	tmp = dup(pipex->commands->fdin);
	commands = pipex->commands;
	while (commands != 0)
	{
		pipe(fd);
		if (commands->builtin != 0)
		{
			exe_builtin(pipex, &tmp, fd, commands);
			compact_exe3(pipex, fd, &tmp);
			commands = commands->next;
			continue ;
		}
		reset_sig();
		commands->pid = fork();
		compact_exe2(commands, pipex, fd, &tmp);
		commands = commands->next;
	}
	compact_exe(&tmp, pipex->commands, pipex);
}
