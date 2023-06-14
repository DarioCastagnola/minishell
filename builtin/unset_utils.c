/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char *s, t_pipex *pipex)
{
	char	**mat;
	int		i;

	mat = create_matrix(s);
	cmd_trim(mat);
	i = 0;
	while (mat[++i])
	{
		unset_args(mat[i], pipex);
	}
	i = -1;
	while (mat[++i])
	{
		free(mat[i]);
	}
	free(mat);
}
