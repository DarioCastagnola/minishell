/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:02:17 by dcastagn          #+#    #+#             */
/*   Updated: 2023/05/11 14:26:17 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	handle_quotes(char *input)
// {
// 	int i = 0;
// 	while (input[i] != '\0')
// 	{
// 		if (input[i] == '\'')
// 		{
// 			while (input[++i] != '\'')
// 				;
// 		}
// 		if (input[i] == '\"')
// 		{
// 			while (input[++i] != '\"')
// 				;
// 		}
// 		i++;
// 	}
// 	return(i);
// }

int ft_isspace(int c)
{
	return (c == ' ') || (c == '\f') ||
		(c == '\n') || (c == '\r') || (c == '\t') || (c == '\v');
}

char	*recognize_filename(char *str, int i)
{
	int		filename_index;
	char	*filename;

	filename_index = 0;
	filename = malloc(sizeof(char) * 256);
	if (!filename)
		perror("Errore allocazione filename redirection");
	if (str[i + 1] == '>')
		{
			i += 1;
			while (ft_isspace(str[++i]))
				;
			while (!ft_isspace(str[i]) && str[i] != '\0' && filename_index < 255)
				filename[filename_index++] = str[i++];
		}
		else
		{
			while (ft_isspace(str[++i]))
				;
			while (!ft_isspace(str[i]) && str[i] != '\0' && filename_index < 255)
				filename[filename_index++] = str[i++];
		}
		filename[filename_index] = '\0';
		return (filename);
}

void	redict(char **input)
{
	int		i;
	int		j;
	int		fd;
	int		filename_index;
	char	filename[256];

	filename_index = 0;
	i = -1;
	j = 0;
	while (++i < strlen(input[j][i]))
	{
		if (input[j][i] == '\'')
			while (input[j][++i] != '\'')
				;
		if (input[j][i] == '\"')
			while (input[j][++i] != '\"')
				;
		if (input[j][i] == '>')
		{
			if (input[j][i + 1] == '>')
			{
				i += 1;
				while (isspace(input[j][++i]))
					;
				while (!isspace(input[j][i]) && input[j][i] != '\0' && filename_index < 255)
					filename[filename_index++] = input[j][i++];
				fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd < 0)
				{
					perror("Error cannot open file\n");
					exit(1);
				}
			}
			while (isspace(input[j][++i]))
				;
			while (!isspace(input[j][i]) && input[j][i] != '\0' && filename_index < 255)
				filename[filename_index++] = input[j][i++];
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("Error cannot open file\n");
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) < 0)
			{
				perror("Error cannot redirect output");
				exit(1);
			}
			close(fd);
		}
		if (input [j][i]  == '<')
		{
			//should redirect output
		}
}

