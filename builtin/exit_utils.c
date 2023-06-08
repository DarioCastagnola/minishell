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
	i = -1;
	while (s[++i])
	{
		if (s[i] < 48 || s[i] > 57)
		return (1);
	}
	return (0);
}

void	ft_exit(char *s, t_pipex *pipex)
{
	char	**mat;
	int		i;
	int		n;

	mat = create_matrix(s);
	cmd_trim(mat);
	i = 0;
	while(mat[i])
		i++;
	if (i > 2)
		write (2, "Minishell: exit: too many arguments\n", 37);
	else if (i == 1)
	{
		free_mat(mat);
		write(1, "exit\n", 5);
		free_total(pipex);
		exit (0);
	}
	else if (exit_num(mat[1]) == 1)
	{
		write (2, "Minishell: exit: a numeric argument is required\n", 49);
		free_mat(mat);
		free_total(pipex);
		exit (2);
	}
	else
	{
	n = ft_atoi(mat[1]);
	write(1, "exit\n", 5);
	free_mat(mat);
	free_total(pipex);
	exit (n);
	}
}
