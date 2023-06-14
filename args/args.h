/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfiliagg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/03/21 09:17:08 by dfiliagg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

typedef struct s_args
{
	char			*key;
	char			*value;
	struct s_args	*next;
}	t_args;

void	add_arg(t_args *arg, t_pipex *pipex);
void	print_args(t_pipex *pipex);
void	free_args(t_pipex *pipex);
int		ft_strcmp_args(char *s1, char *s2);
void	unset_args(char *key, t_pipex *pipex);
char	*get_var(char *key, t_pipex *pipex);
char	*sost_arg(char *s, t_pipex *pipex);
void	var_mat(t_pipex *pipex, char **mat);
void	add_ordered(t_args *new, t_pipex *pipex);
void	add_arg(t_args *arg, t_pipex *pipex);
int		check_args(t_args *arg, t_pipex *pipex);

#endif