/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:43:38 by dcastagn          #+#    #+#             */
/*   Updated: 2023/05/16 11:25:03 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	return ((c == ' ') || (c == '\f')
		|| (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v'));
}

int	ft_heredoc(const char *terminator)
{
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, terminator) == 0)
		{
			free(line);
			break ;
		}
	}
	free(line);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
