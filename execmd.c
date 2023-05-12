/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:34:07 by dcastagn          #+#    #+#             */
/*   Updated: 2023/05/09 10:42:11 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execmd(char **argv)
{
	char	*command;

	if (argv)
	{
		command = argv[0];
		if (execve(command, argv, NULL) == -1)
			;
	}
}
