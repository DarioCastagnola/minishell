/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	c_value(int *i, char *value, char *s)
{
	int	j;

	j = 0;
	while (s[*i])
	{
		value[j] = s[*i];
		j++;
		*i = *i + 1;
	}
	value[j] = 0;
}

void	c_key(int *i, char *key, char *s)
{
	int	j;

	j = 0;
	while (s[*i] && s[*i] != '=')
	{
		key[j] = s[*i];
		j++;
		*i = *i + 1;
	}
	key[j] = 0;
}

void	add_export_string(t_args *arg, char *key, char *value, t_pipex *pipex)
{
	arg->value = sost_arg(value, pipex);
	arg->key = ft_strdup(key);
	add_arg(arg, pipex);
}

void	export_string(char *s, t_pipex *pipex)
{
	int		i;
	char	*key;
	char	*value;
	t_args	arg;

	i = 0;
	while (s[i] && !ft_isalpha(s[i]))
		i++;
	key = malloc(ft_strlen(s));
	c_key(&i, key, s);
	if (!s[i])
	{
		free(key);
		return ;
	}
	if (s[i] == '=')
		i++;
	value = malloc(ft_strlen(s));
	c_value(&i, value, s);
	if (exist_ambient_var(key, pipex) == 1)
		set_ambient(key, value, pipex);
	else
		add_export_string(&arg, key, value, pipex);
	free(value);
	free(key);
}

char	**parsing_export_final(char *s, t_pipex *pipex)
{
	char	*str;
	char	**mat;

	(void)pipex;
	mat = parsing_export(s);
	compact_mat(mat);
	str = mat_to_string(mat);
	free_mat(mat);
	mat = parsing_export(str);
	free(str);
	cmd_trim(mat);
	compact_mat(mat);
	mat = remove_space_from(mat);
	return (mat);
}
