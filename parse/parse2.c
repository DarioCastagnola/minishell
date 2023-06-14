/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	compact_se_red_out(int *i, char **mat, t_commands *com)
{
	int	fd;

	if (ft_strcmp_args(mat[*i], ">") == 0 && mat[*i + 1][0] != '>')
	{
		*i = *i + 1;
		if (mat[*i] == 0 || mat[*i][0] == '|' || mat[*i][0] == '<')
			return (1);
		mat[*i] = trim_red(mat[*i]);
		fd = open(mat[*i], O_CREAT | O_RDWR | O_CREAT, 0666);
		if (fd < 0)
			return (1);
		else
			close (fd);
		com->fileout = mat[*i];
		com->redout = 1;
		*i = *i +1;
	}
	return (0);
}

int	set_red_out(char **mat, int *i, t_commands *com)
{
	int	fd;

	if (!mat[*i])
		return (0);
	if (ft_strcmp_args(mat[*i], ">") == 0 && !mat[*i + 1])
		return (1);
	if (ft_strcmp_args(mat[*i], ">") == 0 && mat[*i + 1][0] != '>')
		return (compact_se_red_out(i, mat, com));
	if (ft_strcmp_args(mat[*i], ">") == 0 && mat[*i + 1][0] == '>')
	{
		*i = *i + 2;
		if (mat[*i] == 0 || mat[*i][0] == '|'
			|| mat[*i][0] == '<' || mat[*i][0] == '>')
			return (1);
		mat[*i] = trim_red(mat[*i]);
		fd = open(mat[*i], O_APPEND | O_RDWR | O_CREAT, 0666);
		if (fd < 0)
			return (1);
		else
			close (fd);
		com->fileout = mat[*i];
		com->redout = 2;
		*i = *i + 1;
	}
	return (0);
}

int	compact_set_red_in(char **mat, int *i, t_commands *com)
{
	*i = *i + 1;
	if (mat[*i] == 0 || mat[*i][0] == '|'
		|| mat[*i][0] == '>' || access(mat[*i], F_OK))
		return (1);
	mat[*i] = trim_red(mat[*i]);
	com->filein = mat[*i];
	com->redin = 1;
	*i = *i + 1;
	return (0);
}

int	set_red_in(char **mat, int *i, t_commands *com)
{
	if (!mat[*i])
		return (0);
	if (ft_strcmp_args(mat[*i], "<") == 0 && !mat[*i + 1])
		return (1);
	if (ft_strcmp_args(mat[*i], "<") == 0 && mat[*i + 1][0] != '<')
		return (compact_set_red_in(mat, i, com));
	if (ft_strcmp_args(mat[*i], "<") == 0 && mat[*i + 1][0] == '<')
	{
		*i = *i + 2;
		if (mat[*i] == 0 || mat[*i][0] == '|'
			|| mat[*i][0] == '>' || mat[*i][0] == '<')
			return (1);
		mat[*i] = trim_red(mat[*i]);
		com->filein = mat[*i];
		com->redin = 2;
		*i = *i + 1;
		return (0);
	}
	return (0);
}

void	compact_parse4(t_commands *com, int *i, char **mat)
{
	com->redin = 0;
	com->redout = 0;
	com->builtin = return_builtin(mat, i);
}
