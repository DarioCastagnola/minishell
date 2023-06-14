/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	com_ex(t_commands *commands, t_pipex *pipex)
{
	char	**mat;

	mat = create_matrix(commands->args);
	cmd_trim(mat);
	ft_cd(mat, pipex);
	free_mat(mat);
}

void	compact_exe_builtin(t_commands *commands, t_pipex *pipex)
{
	if (ft_strncmp(commands->args, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(commands->args, "exit", 4) == 0)
		ft_exit(commands->args, pipex);
	else if (ft_strncmp(commands->args, "export", 6) == 0)
		export_mat(pipex, commands->args);
	else if (ft_strncmp(commands->args, "unset", 5) == 0)
		ft_unset(commands->args, pipex);
	else if (ft_strncmp(commands->args, "echo", 4) == 0)
		our_echo(commands->args);
	else if (ft_strncmp(commands->args, "cd", 2) == 0)
		com_ex(commands, pipex);
	else if (ft_strncmp(commands->args, "env", 5) == 0)
	{
		ft_env(pipex);
		print_args(pipex);
	}
	if (pipex->exit_builtin == 0)
		g_exitcode = 0;
}

void	exe_builtin(t_pipex *pipex, int *fd, int *pip, t_commands *commands)
{
	if ((commands->builtin == 2 && commands->next != 0)
		|| (commands != pipex->commands && commands->builtin == 2))
		return ;
	if (commands->redout == 0 && commands->next == 0)
		dup2(pipex->stdout, 1);
	else if (commands->redout != 0)
		dup2(commands->fdout, 1);
	else
		dup2(pip[1], 1);
	close(pip[1]);
	close(*fd);
	compact_exe_builtin(commands, pipex);
}

int	is_path(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != 0)
	{
		if (s[i] == '/')
			return (1);
	}
	return (0);
}
