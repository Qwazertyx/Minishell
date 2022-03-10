#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_var
{
	char	**cmd;
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
t_var	*parse(char *a);
int		execmaster(char **maincmd, char **envp);
char	*path(char *cmd, char **envp);
char	*ft_strdup(char *a);
int		ft_vpipe(t_var *tab, int nb, char **env);
int		ft_choice(t_var *tab, char **env, int i);
int		echomaster(char *cmd);
void	ft_exit(t_var *tab, int nb);
void	free_tab(t_var *a);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_pwd(void);
void	ft_env(char **env);
void	ft_putstr_fd(char *s, int fd);
char	**ft_splitve(char *arg, char c, char *cmd);
int		mycd(char **cmd);
int		ft_putchar(int c);
int		is_input(char *s);
int		ft_strcmp(char *a, char *b);
char	*ft_joinc(char *s1, char c);
char	*ft_joins(char *s1, char *s2);
int		ft_strchrquot(char *s, char c, char c2);
int		s_chevred(char *ch);
char	*ft_strncpy(char *dest, char *str, int n);
char	*ft_strndup(char *a, int l);
char	*ft_nochevre(char *s, char c);
char	*ft_noquote(char *a);

#endif
