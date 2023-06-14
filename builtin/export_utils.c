/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*mat_to_string_export(char **mat)
{
	int		i;
	char	*arg;
	char	*tmp;

	i = 0;
	arg = ft_strdup("");
	while (mat[i])
	{
		tmp = ft_strjoin(arg, "");
		free(arg);
		arg = ft_strjoin(tmp, mat[i]);
		free(tmp);
		i++;
	}
	free(arg);
	return (tmp);
}

void	export_trim(char **mat)
{
	int		i;
	char	*tmp;

	i = -1;
	while (mat[++i])
	{
		if (mat[i][0] == '"')
		{
			tmp = ft_strtrim(mat[i], "\"");
			free (mat[i]);
			mat[i] = tmp;
		}
		if (mat[i][0] == '\'')
		{
			tmp = ft_strtrim(mat[i], "'");
			free(mat[i]);
			mat[i] = tmp;
		}
	}
}

void	export_mat(t_pipex *pipex, char *str)
{
	int		i;
	char	**mat;

	if (!str[6])
	{
		ft_blankexport(pipex);
		return ;
	}
	i = -1;
	mat = parsing_export_final(pipex->input, pipex);
	while (mat[++i])
	{
		if (!ft_isalpha(mat[i][0]) && mat[i][0] != '_')
		{
			pipex->exit_builtin = 1;
			g_exitcode = 1;
			write(2, "Minishell: bad identifier\n", 27);
			continue ;
		}
		if (contain_equals(mat[i]))
			export_string(mat[i], pipex);
	}
	free_mat(mat);
}
