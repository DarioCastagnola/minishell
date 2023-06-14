/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_num(char *s)
{
	int	i;

	if (!s)
		return (0);
	if ((s[0] == '-' || s[0] == '+') && !s[1])
		return (1);
	if ((s[0] < 48 || s[0] > 57) && (s[0] != '-' && s[0] != '+'))
		return (1);
	i = 0;
	while (s[++i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (1);
	}
	return (0);
}

void	compact_exit(char **mat, t_pipex *pipex)
{
	free_mat(mat);
	write(1, "exit\n", 5);
	free_total(pipex);
	g_exitcode = 0;
	pipex->exit_builtin = 1;
	exit (0);
}

void	compact_exit2(char **mat, t_pipex *pipex)
{
	write (2, "Minishell: exit: a numeric argument is required\n", 49);
	free_mat(mat);
	free_total(pipex);
	g_exitcode = 2;
	exit (2);
}

void	c_exit(t_pipex *pipex)
{
	pipex->exit_builtin = 1;
	write (2, "Minishell: exit: too many arguments\n", 37);
	g_exitcode = 1;
}

void	ft_exit(char *s, t_pipex *pipex)
{
	char	**mat;
	int		i;
	int		n;

	mat = create_matrix(s);
	cmd_trim(mat);
	i = 0;
	while (mat[i])
		i++;
	if (i > 2)
		c_exit(pipex);
	else if (i == 1)
		compact_exit(mat, pipex);
	else if (exit_num(mat[1]) == 1)
		compact_exit2(mat, pipex);
	else
	{
		n = ft_atoi(mat[1]);
		write(1, "exit\n", 5);
		free_mat(mat);
		free_total(pipex);
		pipex->exit_builtin = 1;
		g_exitcode = n;
		exit (n);
	}
}
