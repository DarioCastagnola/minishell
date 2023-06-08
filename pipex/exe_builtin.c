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

void	exe_builtin(t_pipex *pipex, int *fd, int *pip, t_commands *commands)
{
	char	**mat;
    if ((commands->builtin == 2 && commands->next != 0) || (commands != pipex->commands && commands->builtin == 2))
        return;
    if (commands->redout == 0 && commands->next == 0)
		dup2(pipex->stdout, 1);
	else if (commands->redout != 0)
	    dup2(commands->fdout, 1);	
	else
		dup2(pip[1], 1);
	close(pip[1]);
	close(*fd);
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
	{	
		mat = create_matrix(commands->args);
		cmd_trim(mat);
        ft_cd(mat, pipex);
		free_mat(mat);
	}
	else if (ft_strncmp(commands->args, "env", 5) == 0)
	{
        ft_env(pipex);
		print_args(pipex);
	}
}

int	is_path(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != 0)
	{
		if (s[i] == '/')
			return(1);
	}
	return (0);
}