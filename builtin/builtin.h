/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/05/26 11:42:53 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
//ENV
void	ft_create_envp(t_pipex *pipex, char **envp);
void	free_envp(t_pipex *pipex);
void	ft_env(t_pipex *pipex);
//PWD
void	ft_pwd(void);
//EXPORT
char	**parsing_export(char *s);
void	export_mat(t_pipex *pipex, char *s);
char	**parsing_export_final(char *s, t_pipex *pipex);
void	ft_blankexport(t_pipex *pipex);
char	**remove_space_from(char **mat);
void	compact_mat(char **mat);
char	**parsing_export(char *s);
int		contain_equals(char *s);
void	export_mat(t_pipex *pipex, char *str);
void	export_string(char *s, t_pipex *pipex);
//ECHO
char	**preparsed_filter(char **strs);
void	free_mat(char **mat);
void	printwoquotes(char *cmd);
void	echo_print(char **str, int i, int flag);
int		echoflagcheck(char *str);
void	our_echo(char *argv);
//CD
int		ft_cd(char **str, t_pipex *pipex);
void	*ft_realloc(void *ptr, size_t size);
//EXIT
void	ft_exit(char *s, t_pipex *pipex);
//UNSET
void	ft_unset(char *s, t_pipex *pipex);

#endif
