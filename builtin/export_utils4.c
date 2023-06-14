/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**remove_space_from(char **mat)
{
	int		i;
	int		count;
	char	**newmat;

	i = -1;
	count = 1;
	while (mat[++i])
	{
		if (mat[i][0] != ' ')
			count++;
	}
	newmat = malloc(sizeof(char **) * count);
	i = -1;
	count = 0;
	while (mat[++i])
	{
		if (mat[i][0] != ' ')
		{
			newmat[count] = ft_strdup(mat[i]);
			count++;
		}
	}
	newmat[count] = 0;
	free_mat(mat);
	return (newmat);
}

void	compact_mat(char **mat)
{
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	while (mat[i])
		i++;
	i--;
	j = i;
	while (i > 0)
	{
		if (mat[i][0] != ' ' && mat[i - 1][0] != ' ')
		{
			tmp = ft_strjoin(mat[i - 1], mat[i]);
			free(mat[i]);
			free(mat[i - 1]);
			mat[i] = ft_strdup(" ");
			mat[i -1] = tmp;
			i = j;
		}
		i--;
	}
}

char	**parsing_export(char *s)
{
	int		i;
	char	**mat;
	char	*wrd;

	i = -1;
	mat = malloc(sizeof(char *) * 1);
	mat[0] = 0;
	while (s[++i])
	{
		if (s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == ' ')
			mat = add_chr(mat, s[i]);
		else if (s[i] == '\'' || s[i] == '"')
		{
			wrd = fnd_qts(s, &i);
			mat = add_wrd(mat, wrd);
			continue ;
		}
		else
		{
			wrd = fnd_wrd(s, &i);
			mat = add_wrd(mat, wrd);
		}
	}
	return (mat);
}

int	contain_equals(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			return (1);
	}
	return (0);
}
