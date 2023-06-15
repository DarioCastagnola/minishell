/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:44:08 by dcastagn          #+#    #+#             */
/*   Updated: 2023/06/06 12:00:09 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_mat_reverse(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	i--;
	while (i > -1)
	{
		if (ft_strcmp_args(mat[i], "?"))
			printf("declare -x %s\"\n", mat[i]);
		i--;
	}
}

char	**create_empty_export_mat(t_pipex *pipex)
{
	int		i;
	t_args	*tmp;
	char	**mat;

	i = 0;
	if (!pipex->args)
		return (0);
	tmp = pipex->args;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	mat = malloc(sizeof(char **) * (i + 1));
	return (mat);
}

void	print_argsexp(t_pipex *pipex)
{
	t_args	*tmp;
	int		i;
	char	**mat;
	char	*s;
	char	*s2;

	mat = create_empty_export_mat(pipex);
	if (!pipex->args)
		return ;
	i = -1;
	tmp = pipex->args;
	while (tmp)
	{
		if (ft_strcmp_args(tmp->key, "?"))
		{
			s = ft_strjoin(tmp->key, "=\"");
			s2 = ft_strjoin(s, tmp->value);
			free(s);
			mat[++i] = s2;
		}
		tmp = tmp->next;
	}
	mat[++i] = 0;
	print_mat_reverse(mat);
	free_mat(mat);
}

void	ft_blankexport(t_pipex *pipex)
{
	char	*str;
	int		i;

	i = -1;
	while (pipex->envp[++i])
	{
		str = ft_strjoin("declare -x ", pipex->envp[i]);
		printf("%s\n", str);
		free(str);
	}
	print_argsexp(pipex);
}
