/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sost_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_mat(t_pipex *pipex, char **mat)
{
	int		i;
	char	*tmp;

	i = -1;
	while (mat[++i])
	{
		if (mat[i][0] == '\'')
			continue;
		tmp = sost_arg(mat[i], pipex);
		free(mat[i]);
		mat[i] = tmp;
	}
}

char	*get_name_var(char *s, int *i)
{
	char	*var;
	int		j;

	*i = *i + 1;
	j = *i;
	if (s[j] == '?')
		return (ft_strdup("?"));
	while (s[j] && ft_isalnum(s[j]))
		j++;
	var = malloc(j + 1);
	j = 0;
	while (s[*i] && ft_isalnum(s[*i]))
	{
		var[j] = s[*i];
		*i = *i + 1;
		j++;
	}
	var[j] = 0;
	if (j != 0)
		return (var);
	free(var);
	return (0);
}

char	*add_var2string(int *i, t_pipex *pipex, char	*s, char *new)
{
	char	*key;
	char	*value;

	value = "";
	key = get_name_var(s, i);
	if (key != 0)
	{
		value = get_var(key, pipex);
		free(key);
	}
	if (value)
	{
		key = ft_strjoin(new, value);
		free(new);
		return (key);
	}
	return (new);
}

char	*cpy_str(char *newstr, char s)
{
	char	*tmp;
	int		j;

	tmp = ft_strdup(newstr);
	free(newstr);
	newstr = malloc(ft_strlen(tmp) + 2);
	j = -1;
	while (tmp[++j])
		newstr[j] = tmp[j];
	free(tmp);
	newstr[j] = s;
	newstr[++j] = 0;
	return(newstr);
}

char	*sost_arg(char *s, t_pipex *pipex)
{
	int		i;
	char	*newstr;

	i = -1;
	newstr = ft_strdup("");
	while (s[++i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?')
			{
				newstr = add_var2string(&i, pipex, s, newstr);
				i++;
			}
			else if (s[i + 1] && ft_isalpha(s[i + 1]))
			{
				newstr = add_var2string(&i, pipex, s, newstr);
			}
			else if (s[i + 1] && s[i + 1] >=48 && s[i + 1] <= 57 && s[i + 1])
			{
				if(s[i + 2])
					i += 1;
			}
		}
		if (!s[i])
			return (newstr);
		newstr = cpy_str(newstr, s[i]);
	}
	return (newstr);
}