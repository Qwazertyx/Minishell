/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:07:02 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 15:38:12 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>

# ifndef G_EXIT
#  define G_EXIT

int	g_exit;

# endif

typedef struct s_var
{
	char	***cmd;
	char	***env;
	char	***chevred;
	char	***chevreg;
	int		*heredocfd;
}				t_var;

//CD
void	cd(char **path, char **env, t_var *p);

//CHEVRE
int		nb_schevre(char *ch, char c);
char	*ft_chevrecpy(char *ch, char c1, char c2);
char	**ft_sfilechevre(char *ch, char c);
char	*no_endspace(char *s);

//CHEVREREDIR
int		whoislastdouble(char **file);
void	readline_doublechevre(char **file, char *stop, int pipefd[2], int i);
int		doublechevre(char **file, int i);
int		ft_while_chevreg(char **file, t_var *tab, int i, int j);
int		ft_chevreg(char **file, t_var *tab, int j);

//CHEVREUTILS
char	*no_chevre(char *s, char c);
char	*ft_nochevre(char *s, char c);
char	*filename(char *s);
int		end_chevre(char **file, int param);
int		ft_chevred(char **file);

//CHEVREUTILS2
int		skip_next_word(char *s, char c);
int		has_a_single(char **chevre);
int		all_chevre(t_var *tab, int i, int fd[2]);

//CHOICE
int		read_heredoc(t_var *tab, int *status, int nb);
pid_t	ft_vpipe(t_var *tab, int nb, int i);
pid_t	ft_execve(t_var *tab, int i, pid_t pid, int fd[2]);
void	ft_functions(t_var *tab, int i, pid_t pid, int fd[2]);
pid_t	ft_choice(t_var *tab, int i, pid_t pid);

//ECHO
int		*get_sus(char **envp, char *toech, int j);
int		echospecial(char *cmd, char **envp, int i);
int		nparam(char *cmd);
int		echoservant(char *cmd, int i);
int		echomaster(char *cmd);

//ENV_NULL
char	*ft_joinsfree2(char *a, char *b);
char	**free_bf_i(char **env, int i);
char	**fill_null_env(void);

//ENV
int		ft_strcmtri(char **env, int i);
int		*ft_nbcreate(char **env);
void	ft_env(char **env);

//EXEC
int		execmaster(char **maincmd, char **env);

//EXIT
int		is_num(char *a);
int		verif_exit(char *cmd);
long	ft_atol(char *str);
void	ft_exit(t_var	*tab, int i, int nb, char **cmd);

//EXITUTILS
int		ft_strleni(char *a, int i);
int		ft_strcmpi(char *a, char *b, int i);

//EXPAND_DOLAR
int		stop_while(char c, char *legal);
char	*ft_dolar(char *a, char **env);
int		skip_dolar(char *cmd);

//EXPORT
char	**env_cpy(char **env, char **cmd);
char	**add_export(char **cmd, char **env, int i);
char	*fill_export(char *cmd, int nb, int i);
char	**free_pre_parse(char **pre, int i);
char	**utils_pre_parsexport(char *cmd, int nb);

//EXPORTEXIT
void	exit_export(t_var *p, int i);

//EXPORTUTILS
char	**pre_parsexport(char *cmd);
char	*end_parse(char *a);
char	**create_tab_parse(char **tab, char *to_add);
void	export_exist(char *mod, char **env);
char	**parse_export(char *cmd, char **env, int i, char **final);

//EXPORTUTILS2
void	print_export(char **env);
int		only_onechar(char *a, char c);
int		secu_export(char *cmd);
void	export(char *cmd, t_var *p);
char	*only_noquote(char *a, int i, char *s, char quot);

//FT_ATOI
int		ft_atoi(const char *str);
char	*remp(char *tab, int nb, int l, int s);
char	*ft_itoa(int n);

//FT_FREE
int		ft_free_i(t_var *p, char *a, int i, int j);
t_var	*free_returned(t_var *p, char *a);
void	free_cmd(char ***cmd);
void	free_struc(t_var *p, int i);
void	ft_close(t_var *p);

//FT_JOIN
char	*ft_joinc(char *s1, char c);
char	*ft_joins(char *a, char *b);
char	*ft_joinsfree(char *a, char *b);
char	*fill_ft_noquote(char *a, int len);
char	*ft_noquote(char *a);

//GETENV
int		ft_startcomparegal(char *s1, char *s2);
int		ft_startcompare(char *s1, char *s2);
char	*ft_getenv(char	*var, char **env);
int		ft_existcompare(char *s1, char *s2);
int		ft_exist(char *var, char **env);

//HEREDOC
void	ft_while_doublechevre(int *pipes[2], char ***file, int ij[2],
			char **env);
int		ft_doublechevre(int *pipes[2], char ***file, char **env);
void	fill_pipes(char ***file, int *pipes[2]);
int		*ft_heredoctest(char ***file, char **env);

//MAIN
void	ft_useread(t_var *parsed, char *a);
void	ft_while(t_var *parsed);
char	**prep_env(char **envp);

//MULTIPIPEX
void	callerror(const char *s);
void	ft_fatherpipex(int *fd, int nb, int *old, int i);
pid_t	multipipex(t_var *tab, int nb, int *old, int i);

//PARSE
char	*place_split(char *a, int nb);
char	*ft_no_doublespace(char *s);
char	*ft_parsechevre(char *a, t_var *p);
int		ft_fill_cmd(char *a, t_var *p, int i);
t_var	*parse(char *a, t_var *p);

//PARSEUTILS
int		nb_param(char *a);
char	*special_joinsfree_skip(char *a, char **b, char *s, int *i);
char	*skip_quote(char *cmd, int n, char **env, char *s);
char	*f_split(char *a);
char	*l_split(char *a);

//PIPEXERROR
void	terminate(void);
void	errorcmd(char *cmd);
void	free_split(char **args);

//PIPEXPATH
char	**get_paths(char **envp);
char	*path(char *cmd, char **env);

//PIPEXUTILS
int		ft_strlen(char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);

//PRINTS
void	ft_putstr_fd(char *s, int fd);
int		ft_putchar(int c);
int		contains(char *a, char c);
void	ft_putendl_fd(char *s, int fd);

//PROMPT
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_prompt(void);

//PWD
void	ft_pwd(void);

//SIGHOLDERS
void	ctrl_c(int sig);
void	ctrl_bs(int sig);
void	sig_heredoc(int sig);
void	func_sig(int sig);
void	useless_sig(int sig);

//SPLITQUOTE
char	**ft_splitquote(char *arg, char c);

//SPLIT
char	**ft_split(char const *s, char c);

//SPLITVE
char	**ft_splitve(char *arg, char c, char *cmd);

//STRCHRCMP
pid_t	ft_strcmp(char *a, char *b);
int		ft_strchrquot(char *s, char c, char c2);
int		ft_strchr(char *a, char c);

//UNSET
int		len_delete_tab(char **cmd, char **env);
char	**delete_tab(char **cmd, char **env);
char	**unset(char **cmd, char **env);

//UTILS
int		ft_isexportable(char *s);
void	ft_normal_fd(int fd[2]);
char	*ft_strdup(char *a);
char	*ft_strndup(char *a, int l);

//VERIF_PARSE
int		ft_verifchevred(t_var *p);
int		ft_verifchevreg(t_var *p);
int		ft_verifchevre(t_var *p);
int		is_input(char *s);
int		nb_doublt(char *a);

#endif
