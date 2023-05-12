/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:22:17 by dcastagn          #+#    #+#             */
/*   Updated: 2023/05/09 10:55:08 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void handle_single_quotes(char *input, char *output)
{
	int	i;
	int	in_quotes;
	int	j;

	j = 0;
	i = 0;
	in_quotes = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			in_quotes = !in_quotes;
		}
		else if (in_quotes)
		{
			output[j++] = input[i];
			input[i] == '\0';
		}
		else
		{
			// Handle other characters
		}
	i++;
	}
	output[j] = '\0';
}

void handle_double_quotes(char *input, char *output)
{
	int	i;
	int	in_quotes;
	int	allow_variables;

	i = 0;
	in_quotes = 0;
	allow_variables = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			in_quotes = !in_quotes;
		else if (input[i] == '\"')
		{
			in_quotes = !in_quotes;
			allow_variables = !allow_variables;
		}
		else if (in_quotes)
			output[i] = input[i];
		else if (input[i] == '$' && allow_variables)
		{
			// Expand variable
		}
		else
		{
			// Handle other characters
		}
	i++;
	}
}

void	parser(char *line)
{
	char	*input;
	char	output[1024];
	char	*tokens[64];
	int		num_tokens;
	char	*token;

	while (42)
	{
		input = readline("$ ");
		if (input == NULL)
		{
			printf("\n");
			exit(0);
		}
	handle_single_quotes(input, output);
	handle_double_quotes(output, input);
	token = ft_split(input, " ");
	num_tokens = 0;

	while (token != NULL && num_tokens < 64)
	{
      tokens[num_tokens++] = token;
      token = ft_split(NULL, " ");
    }

    // Execute command
	if (num_tokens > 0)
	{
		if (strcmp(tokens[0], "exit") == 0)
			exit(0);
		else
		{
			// Handle other commands
		}
	}

	// Free input buffer
	free(input);
	}
	return (0);
}
*/
