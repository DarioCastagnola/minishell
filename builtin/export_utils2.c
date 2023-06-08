/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/06/08 16:32:06 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**remove_space_from(char **mat)
{
	int		i;
	int 	count;
	char	**newmat;

	i = -1;
	count = 0;
	while(mat[++i])
	{
		if (mat[i][0] != ' ')
			count++;
	}
	count++;
	newmat = malloc(sizeof(char **) *count);
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
	int 	j;

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
			mat[i] =ft_strdup(" ");
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
			continue;
		}
		else
		{
			wrd = fnd_wrd(s, &i);
			mat = add_wrd(mat, wrd);
		}
	}
	return (mat);
}

int contain_equals(char *s)
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

void	export_string(char *s, t_pipex *pipex)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	t_args	arg;

	i = 0;
	while (s[i] && !ft_isalpha(s[i]))
		i++;
	key = malloc(ft_strlen(s));
	j = 0;
	while (s[i] && s[i] != '=')
	{
		key[j] = s[i];
		j++;
		i++;
	}
	key[j] = 0;
	if (!s[i])
	{
		free(key);
		return;
	}
	if (s[i] == '=')
		i++;
	value = malloc(ft_strlen(s));
	j = 0;
	while (s[i])
	{
		value[j] = s[i];
		j++;
		i++;
	}
	value[j] = 0;
	i = -1;
	while (pipex->envp[++i])
	{
		if (ft_strncmp(key, pipex->envp[i], ft_strlen(key)) == 0)
		{
			set_path(value, pipex);
			free(value);
			free(key);
			return;
		}
	}
	arg.value = sost_arg(value, pipex);
	arg.key= ft_strdup(key);
	add_arg(&arg, pipex);
	free(value);
	free(key);
}

void export_mat(t_pipex *pipex, char *str)
{
	int		i;
	char	**mat;

	if (!str[6])
		ft_blankexport(pipex);
	i = -1;
	mat = parsing_export_final(pipex->input, pipex);
	while (mat[++i])
	{
		if (!ft_isalpha(mat[i][0]))
		{
			write(2, "Minishell: bad identifier\n", 27);
			continue;
		}
		if (contain_equals(mat[i]))
			export_string(mat[i], pipex);
	}
	free_mat(mat);
}

char	**parsing_export_final(char *s, t_pipex *pipex)
{
	char	*str;
	char	**mat;

	(void)pipex;
	mat = parsing_export(s);
	compact_mat(mat);
	var_mat(pipex, mat);
	str = mat_to_string(mat);
	free_mat(mat);
	mat = parsing_export(str);
	free(str);
	cmd_trim(mat);
	compact_mat(mat);
	mat = remove_space_from(mat);
	return (mat);
}
