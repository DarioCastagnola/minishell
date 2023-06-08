/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:43:09 by lde-mich          #+#    #+#             */
/*   Updated: 2023/05/08 12:43:26 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	print_mat(char **mat)
{
	int i = -1;

	while(mat[++i])
	{
		printf("%s\n", mat[i]);
	}
}

char	*mat_to_string(char **mat)
{
	int		i;
	char	*arg;
	char	*tmp;

	i = 0;
	arg = ft_strdup("");
	while (mat[i])
	{
		tmp = ft_strjoin(arg, " ");
		free(arg);
		arg = ft_strjoin(tmp, mat[i]);
		free(tmp);
		i++;
	}
	tmp = ft_strtrim(arg, " ");
	free(arg);
	return(tmp);
}