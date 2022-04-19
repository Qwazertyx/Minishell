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

typedef struct s_var
{
	char	***cmd;
	char	***env;
	char	***chevred;
	char	***chevreg;
	char	**heredoc;
}				t_var;

char	*ft_prompt(void);
char	**ft_split(char const *s, char c);
int		ft_strlen(char *s);
int		ft_conststrlen(char const *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void	terminate(void);
void	errorcmd(char *cmd);
void	free_split(char **args);
t_var	*parse(char *a, t_var *p);
int		execmaster(char **maincmd, char **env);
char	*path(char *cmd, char **tab);
char	*ft_strdup(char *a);
void	ft_vpipe(t_var *tab, int nb);
void	ft_choice(t_var *tab, int i);
int		echomaster(char *cmd);
void	ft_exit(t_var *tab, int nb);
void	free_tab(t_var *a);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_pwd(void);
void	ft_env(char **env);
void	ft_putstr_fd(char *s, int fd);
char	**ft_splitve(char *arg, char c, char *cmd);
void	mycd(char **cmd);
int		ft_putchar(int c);
int		is_input(char *s);
int		ft_strcmp(char *a, char *b);
char	*ft_joinc(char *s1, char c);
char	*ft_joins(char *s1, char *s2);
char	*ft_joinsfree(char *s1, char *s2);
int		ft_strchrquot(char *s, char c, char c2);
int		ft_chevred(char **file);
char	*ft_strncpy(char *dest, char *str, int n);
char	*ft_strndup(char *a, int l);
char	*ft_nochevre(char *s, char c);
char	*ft_getenv(char *var, char **env);
char	*ft_noquote(char *a);
int		*ft_nbcreate(char **env);
void	export(char *cmd, t_var *p);
int		contains(char *a, char c);
int		ft_exist(char *var, char **env);
int		ft_startcompare(char *s1, char *s2);
int		ft_startcomparegal(char *s1, char *s2);
char	**unset(char **cmd, char **env);
int		ft_isexportable(char *s);
void	free_cmd(char ***cmd);
pid_t	multipipex(t_var *tab, int nb, int *old, int i);
char	**ft_sfilechevre(char *ch, char c);
int		ft_chevred(char **file);
int		ft_chevreg(char **file, t_var *tab);
char	*ft_strjoin2(char const *s1, char const *s2);

#endif
