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

char	*get_name_var(char *s, int *i)
{
	char	*var;
	int		j;

	*i = *i + 1;
	j = *i;
	if (s[j] == '?')
		return (ft_strdup("?"));
	while (s[j] && s[j] != ' ')
		j++;
	var = malloc(j + 1);
	j = 0;
	while (s[*i] && s[*i] != ' ' && s[*i] != '"')
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

char	*add_var2string(int *i, t_pipex *pipex, char *s, char *new)
{
	char	*key;
	char	*value;

	value = "";
	key = get_name_var(s, i);
	if (key && key[0] == '?' && key[1] == 0)
	{
		free(key);
		value = ft_itoa(g_exitcode);
		key = ft_strjoin(new, value);
		free(value);
		free(new);
		return (key);
	}
	if (key != 0)
	{
		value = get_var(key, pipex);
		free(key);
	}
	if (value)
	{
		key = ft_strjoin(new, value);
		return (free(new), free(value), key);
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
	return (newstr);
}

char	*compact_sost_arg(char *newstr, int *i, char *s, t_pipex *pipex)
{
	newstr = add_var2string(i, pipex, s, newstr);
	*i = *i + 1;
	return (newstr);
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
			if (s[i + 1] && s[i + 1] == '?')
				newstr = compact_sost_arg(newstr, &i, s, pipex);
			else if (s[i + 1] && ft_isalpha(s[i + 1]))
				newstr = add_var2string(&i, pipex, s, newstr);
			else if (s[i + 1] && s[i + 1] >= 48 && s[i + 1] <= 57 && s[i + 1])
			{
				if (s[i + 2])
					i += 1;
			}
		}
		if (!s[i])
			return (newstr);
		newstr = cpy_str(newstr, s[i]);
	}
	return (newstr);
}
