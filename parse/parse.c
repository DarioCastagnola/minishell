/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	compact_parse(char *arg, t_pipex *pipex)
{
	pipex->exit_builtin = 1;
	g_exitcode = 1;
	write(2, "Minishell: Syntax Error\n", 25);
	free(arg);
	free_commands(pipex);
	pipex->commands = 0;
}

void	compact_parse2(char *arg, t_pipex *pipex, t_commands *com)
{
	com->args = ft_strtrim(arg, " ");
	new_commands(com, pipex);
	free(arg);
}

char	*compact_parse3(char *arg, char **mat, int *i)
{
	char	*tmp;

	if (mat[*i][0] != '|' && mat[*i][0] != '>' && mat[*i][0] != '<')
	{
		tmp = ft_strjoin(arg, " ");
		free(arg);
		arg = ft_strjoin(tmp, mat[*i]);
		free(tmp);
		*i = *i + 1;
	}
	return (arg);
}

void	compact_parse5(t_commands *com, int *i, char **mat, int *err)
{
	*err = set_red_in(mat, i, com);
	if (*err != 1)
		*err = set_red_out(mat, i, com);
}

void	parse(char **mat, t_pipex *pipex)
{
	int			i;
	int			err;
	t_commands	com;
	char		*arg;

	i = -1;
	while (mat[++i])
	{
		compact_parse4(&com, &i, mat);
		arg = ft_strdup("");
		while (mat[i] && mat[i][0] != '|')
		{
			compact_parse5(&com, &i, mat, &err);
			if (!mat[i] || mat[i][0] == '|' || err == 1)
				break ;
			arg = compact_parse3(arg, mat, &i);
		}
		if (err == 1)
			compact_parse(arg, pipex);
		if (err == 0)
			compact_parse2(arg, pipex, &com);
		if (!mat[i])
			break ;
	}
}
