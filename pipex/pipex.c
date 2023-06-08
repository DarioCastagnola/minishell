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

int	create_child(t_commands *commands, t_pipex *pipex)
{
	commands->cmd_args = create_matrix(commands->args);
	cmd_trim(commands->cmd_args);
	if (is_path(commands->cmd_args[0]))
	{
		commands->command = commands->cmd_args[0];
		return (0);
	}
	commands->command = get_cmd(pipex->path, commands->cmd_args[0]);
	if (!commands->command)
	{
		child_free(commands);
		msg(ERR_CMD);
		return (1);
	}
	return (0);
}

int	exec(t_pipex *pipex, int *fd, int *pip, t_commands *commands)
{
	if (commands->redout == 0 && commands->next == 0)
		dup2(pipex->stdout, 1);
	else if (commands->redout != 0)
		dup2(commands->fdout, 1);	
	else
		dup2(pip[1], 1);
	close(pip[1]);
	close(pip[0]);
	if (commands->redin == 1)
		dup2(commands->fdin, 0);
	else if (commands->redin == 2)
	{
		in_redirect(commands, pipex);
		dup2(commands->fdin, 0);
	}
	else
		dup2(*fd, 0);
	close(*fd);
	if (create_child(commands, pipex) == 1)
		exit (1);
	execve(commands->command, commands->cmd_args, pipex->envp);
	return (error("error: cannot execute ", commands->command));
}

void	close_parent(int *tmp, int *fd)
{
	close(*tmp);
	close(fd[1]);
	*tmp = fd[0];
}

void	wait_process(int *tmp, t_commands *wp)
{
	close(*tmp);
	while (wp != 0)
	{
		if (wp->builtin == 0 && wp->pid != -1)
		{
			waitpid(wp->pid, &g_exitcode, 0);
		}
		wp = wp->next;
	}
}

void	exe(t_pipex *pipex)
{
	int			tmp;
	int			fd[2];
	t_commands  *wp;
	t_commands	*commands;

	if (!pipex->commands)
		return ;
	create_red(pipex);
	tmp = dup(pipex->commands->fdin);
	wp = pipex->commands;
	commands = pipex->commands;
	while (commands != 0)
	{
		pipe(fd);
		if (commands->builtin != 0)
		{
			exe_builtin(pipex, &tmp, fd, commands);
			tmp = fd[0];
			dup2(pipex->stdin, 0);
			dup2(pipex->stdout, 1);
			commands = commands->next;
			continue;
		}
		commands->pid = fork();
		if (!commands->pid)
			exec(pipex, &tmp, fd, commands);
		else
			close_parent(&tmp, fd);
		commands = commands->next;
	}
	wait_process(&tmp, wp);
	close_red(pipex);
	if (pipex->commands)
		free_commands(pipex);
}