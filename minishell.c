/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/06/13 10:40:21 by adi-fort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitcode;

void	init(char *envp[], t_pipex *pipex, int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		write(2, "Error: Argument\n", 16);
		exit (2);
	}
	save_io(pipex);
	ft_create_envp(pipex, envp);
	ft_shlvl(pipex);
	path(pipex);
	pipex->commands = 0;
	pipex->args = 0;
	ft_signal();
}

void	compact_main(t_pipex *pipex)
{
	char	*s;

	add_history(pipex->input);
	pipex->mat = create_matrix(pipex->input);
	var_mat(pipex, pipex->mat);
	s = mat_to_string(pipex->mat);
	free_mat(pipex->mat);
	pipex->mat = create_matrix(s);
	free(s);
}

void	compact_main2(t_pipex *pipex)
{
	parse(pipex->mat, pipex);
	exe(pipex);
	free_mat(pipex->mat);
	free(pipex->input);
	free_path(pipex);
	path(pipex);
}

void	compact_main3(t_pipex *pipex)
{
	pipex->exit_builtin = 0;
	pipex->input = readline("Minishell> ");
}

int	main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	init(envp, &pipex, argc, argv);
	while (1)
	{
		compact_main3(&pipex);
		if (!pipex.input)
		{
			write(1, "\n", 1);
			free_total(&pipex);
			exit(0);
		}
		else if (pipex.input[0] == 0)
			continue ;
		compact_main(&pipex);
		if (pipex.mat[0] && check_quote(pipex.mat))
		{
			free(pipex.input);
			free_mat(pipex.mat);
			continue ;
		}
		compact_main2(&pipex);
	}
	free_total(&pipex);
	return (0);
}
