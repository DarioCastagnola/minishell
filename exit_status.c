/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/05/30 11:46:33 by adi-fort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_exit_status(t_pipex *pipex)
{
	t_args	arg;

	if (get_var("?", pipex) == 0)
	{
		arg.key = ft_strdup("?");
		arg.value = ft_strdup("0");
		add_arg(&arg, pipex);
	}
}

void	add_exitstatus(t_pipex *pipex)
{
	t_args	arg;

	unset_args("?", pipex);
	arg.key = ft_strdup("?");
	arg.value = ft_itoa(WEXITSTATUS(g_exitcode));
	add_arg(&arg, pipex);
}

int	ft_atoi_shlvl(const char *s)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r'
		|| ft_isalpha(s[i]) || s[i] == '=')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - 48);
		i++;
	}
	return (result * sign);
}

void	ft_shlvl(t_pipex *pipex)
{
	int		i;
	char	*new_value;
	int		j;
	char	*asciij;

	i = -1;
	while (pipex->envp[++i] != NULL)
	{
		if (!ft_strncmp(pipex->envp[i], "SHLVL=", 5))
		{
			j = ft_atoi_shlvl(pipex->envp[i]);
			free(pipex->envp[i]);
			asciij = ft_itoa(++j);
			new_value = ft_strjoin("SHLVL=", asciij);
			free(asciij);
			pipex->envp[i] = new_value;
			return ;
		}
	}
}
