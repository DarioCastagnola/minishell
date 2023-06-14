/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_chr(char **mat, char c)
{
	char	**mat2;
	int		i;
	char	*s;

	i = 0;
	while (mat[i])
		i++;
	mat2 = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (mat[++i])
		mat2[i] = mat[i];
	s = malloc(2);
	s[0] = c;
	s[1] = 0;
	mat2[i] = s;
	i++;
	mat2[i] = 0;
	free(mat);
	return (mat2);
}

char	**add_wrd(char **mat, char *s)
{
	char	**mat2;
	int		i;

	i = 0;
	while (mat[i])
		i++;
	mat2 = malloc(sizeof(char **) * (i + 2));
	i = -1;
	while (mat[++i])
		mat2[i] = mat[i];
	mat2[i] = s;
	i++;
	mat2[i] = 0;
	free(mat);
	return (mat2);
}

char	*fnd_wrd(char *s, int *i)
{	
	int		k;
	int		j;
	char	*s2;

	j = 0;
	k = *i;
	while (s[k] && s[k] != ' ' && s[k] != '|' && s[k] != '<'
		&& s[k] != '>' && s[k] != '"' && s[k] != '\'')
	{
		j++;
		k++;
	}
	s2 = malloc(j + 1);
	j = 0;
	while (s[*i] && s[*i] != ' ' && s[*i] != '|' && s[*i] != '<'
		&& s[*i] != '>' && s[*i] != '"' && s[*i] != '\'')
	{
		s2[j] = s[*i];
		j++;
		*i = *i + 1;
	}
	s2[j] = 0;
	*i = *i - 1;
	return (s2);
}
