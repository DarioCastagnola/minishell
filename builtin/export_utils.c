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
	return(tmp);
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
		free(mat[i]);
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
