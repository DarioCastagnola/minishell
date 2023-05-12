/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:06:23 by dcastagn          #+#    #+#             */
/*   Updated: 2023/05/09 11:24:33 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **argv)
{
	char	*line;

	(void)ac;
	(void)argv;
	while (42)
	{
	printf("%sMinishell%s", CYAN, END);
	line = readline(">$ ");
	if (!line)
		exit(1);
	printf("command not found\n");
	}
	free(line);
	return (0);
}

