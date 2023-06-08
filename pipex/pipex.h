/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:17:05 by dfiliagg          #+#    #+#             */
/*   Updated: 2023/06/08 14:43:29 by dcastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define ERR_CMD "Command not found\n"
# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define REDIN ".redin"

typedef struct s_commands
{
	int					pid;
	int					redout;
	int					redin;
	int					fdin;
	int					fdout;
	char				*args;
	char				**cmd_args;
	char				*command;
	char				*filein;
	char				*fileout;
	struct s_commands	*next;
	int					builtin;
}	t_commands;

typedef struct s_init
{
	char			*input;
	int				stdin;
	int				stdout;
	char			**path;
	char			**envp;
	t_commands		*commands;
	struct s_args	*args;
	char			**mat;
}	t_pipex;

//error.c
int		msg(char *err);
void	msg_error(char *err);
int		error(char *str, char *err);

//pipex_utils.c
void	path(t_pipex *pipex);
char	*get_cmd(char **paths, char *cmd);
void	save_io(t_pipex *pipex);
void	cmd_trim(char **mat);
char	*trim_red(char *s);

//pipex.c
void	exe(t_pipex *pipex);

//check_file.c
void	create_red(t_pipex *pipex);
void	close_red(t_pipex *pipex);

//free.c
void	child_free(t_commands *com);
void	free_total(t_pipex *pipex);
void	free_commands(t_pipex *pipex);

//command_list.c
void	new_commands(t_commands *com, t_pipex *list);

//exe_builtin.c
void	exe_builtin(t_pipex *pipex, int *fd, int *pip, t_commands *commands);
int		is_path(char *s);

//in_redirect.c
void	in_redirect(t_commands *command, t_pipex *pipex);

//path.c
int		find_path(t_pipex *pipex, char *key);
void	unset_pat(t_pipex *pipex, char *key);
void	set_path(char *s, t_pipex *pipex);

#endif
