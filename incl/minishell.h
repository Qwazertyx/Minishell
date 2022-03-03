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

char	*ft_prompt(void);
char	**ft_split(char const *s, char c);
int		ft_strlen(char *s);
int		ft_conststrlen(char const *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void	terminate(void);
void	errorcmd();
void	free_split(char **args);
char	***parse(char *a);
int		execmaster(char **maincmd, char **envp);
char	*path(char *cmd, char **envp);
char	*ft_strdup(char *a);
void	ft_vpipe(char ***tab, int nb, char **env);
void	*ft_choice(char ***tab, char **env, int i);
int		echomaster(char *cmd, char **envp);
void	ft_exit(char ***tab, int nb);
void	free_tab(char ***a);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_pwd(void);
void	ft_env(char **env);
void	ft_putstr_fd(char *s, int fd);
char	**ft_splitve(char *arg, char c, char *cmd);
int		mycd(char *cmd);

#endif
