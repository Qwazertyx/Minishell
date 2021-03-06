##**********##
### COLORS ###
##**********##

BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
VIOLET		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
IGREY		= \x1b[40m
IRED		= \x1b[41m
IGREEN		= \x1b[42m
IYELLOW		= \x1b[43m
IBLUE		= \x1b[44m
IPURPLE		= \x1b[45m
ICYAN		= \x1b[46m
IWHITE		= \x1b[47m
END			= \x1b[0m
UNDERLINE	= \x1b[4m
REV			= \x1b[7m
ERASE		= \033[2K\r

##********##
### NAME ###
##********##
NAME	= minishell

##***************##
### COMPILATION ###
##**************###
CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address #-fsanitize=address -g3
#-framework CoreFoundation
##*******************##
### DIRECTORY PATHS ###
##*******************##
HEADER		= ./incl/minishell.h
MLX			= ./mlx
OBJ_PATH	= ./objs
SRC_PATH	= ./srcs
RL_LIB_DIR	:= -L $(shell brew --prefix readline)/lib
RL_INC_DIR	:= -I $(shell brew --prefix readline)/include

##***********##
### OBJECTS ###
##***********##
SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

##****************##
### SOURCE FILES ###
##****************##
SOURCES	=	cd.c			\
			chevre.c		\
			chevreredir.c	\
			chevreutils.c	\
			chevreutils2.c	\
			choice.c		\
			echo.c			\
			env_null.c		\
			env.c			\
			exec.c			\
			exit.c			\
			exitutils.c		\
			expand_dolar.c	\
			export.c		\
			exportexit.c	\
			exportutils.c	\
			exportutils2.c	\
			ft_atoi.c		\
			ft_free.c		\
			ft_join.c		\
			getenv.c		\
			heredoc.c		\
			main.c			\
			multipipex.c	\
			parse.c			\
			parseutils.c	\
			pipexerror.c	\
			pipexpath.c		\
			pipexutils.c	\
			prints.c		\
			prompt.c		\
			pwd.c			\
			sigholders.c	\
			split.c			\
			splitquote.c	\
			splitve.c		\
			strchrcmp.c		\
			unset.c			\
			utils.c			\
			verif_parse.c	\


##*********##
### RULES ###
##*********##

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER) Makefile
			@mkdir -p objs
			@printf "$(ERASE)$(BLUE)$(UNDERLINE)Compiling:$(END)$(CYAN)$<"
			@${CC} ${RL_INC_DIR} ${CFLAGS} -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
			@${CC} ${RL_LIB_DIR} ${CFLAGS} -lreadline ${OBJS} -o ${NAME}
			@printf "\n$(GREEN)Successful compilation$(END)\n"

mini:	all
		@echo ""
		@echo "$(RED) ▄████ ██░ ██ ▒█████   ██████▄▄▄█████▓    ██▓███▄    █    ▄▄▄█████▓██░ ██▓█████      ██████ ██░ ██▓█████ ██▓    ██▓     $(END)"
		@echo "$(RED) ██▒ ▀█▓██░ ██▒██▒  ██▒██    ▒▓  ██▒ ▓▒   ▓██▒██ ▀█   █    ▓  ██▒ ▓▓██░ ██▓█   ▀    ▒██    ▒▓██░ ██▓█   ▀▓██▒   ▓██▒    $(END)"
		@echo "$(RED)▒██░▄▄▄▒██▀▀██▒██░  ██░ ▓██▄  ▒ ▓██░ ▒░   ▒██▓██  ▀█ ██▒   ▒ ▓██░ ▒▒██▀▀██▒███      ░ ▓██▄  ▒██▀▀██▒███  ▒██░   ▒██░    $(END)"
		@echo "$(RED)░▓█  ██░▓█ ░██▒██   ██░ ▒   ██░ ▓██▓ ░    ░██▓██▒  ▐▌██▒   ░ ▓██▓ ░░▓█ ░██▒▓█  ▄      ▒   ██░▓█ ░██▒▓█  ▄▒██░   ▒██░    $(END)"
		@echo "$(RED)░▒▓███▀░▓█▒░██░ ████▓▒▒██████▒▒ ▒██▒ ░    ░██▒██░   ▓██░     ▒██▒ ░░▓█▒░██░▒████▒   ▒██████▒░▓█▒░██░▒████░██████░██████▒$(END)"
		@echo "$(RED) ░▒   ▒ ▒ ░░▒░░ ▒░▒░▒░▒ ▒▓▒ ▒ ░ ▒ ░░      ░▓ ░ ▒░   ▒ ▒      ▒ ░░   ▒ ░░▒░░░ ▒░ ░   ▒ ▒▓▒ ▒ ░▒ ░░▒░░░ ▒░ ░ ▒░▓  ░ ▒░▓  ░$(END)"
		@echo "$(RED)  ░   ░ ▒ ░▒░ ░ ░ ▒ ▒░░ ░▒  ░ ░   ░        ▒ ░ ░░   ░ ▒░       ░    ▒ ░▒░ ░░ ░  ░   ░ ░▒  ░ ░▒ ░▒░ ░░ ░  ░ ░ ▒  ░ ░ ▒  ░$(END)"
		@echo "$(RED)░ ░   ░ ░  ░░ ░ ░ ░ ▒ ░  ░  ░   ░          ▒ ░  ░   ░ ░      ░      ░  ░░ ░  ░      ░  ░  ░  ░  ░░ ░  ░    ░ ░    ░ ░   $(END)"
		@echo "$(RED)      ░ ░  ░  ░   ░ ░       ░              ░          ░             ░  ░  ░  ░  ░         ░  ░  ░  ░  ░  ░   ░  ░   ░  ░$(END)"
		@./minishell



clean:
		@rm -f ${OBJS}
		@printf "\n$(BLUE)Object files cleaned\n$(DEF_COLOR)"

fclean:	clean
		@rm -f ${NAME}
		@printf "\n$(CYAN)Executable files cleaned\n$(END)"

re:	fclean
	@${MAKE} all
	@printf "\n$(VIOLET)Cleaned and rebuilt everything\n$(END)"

t:
	gcc -g -lreadline ${SRCS}
	./a.out

sus:
	@echo "$(IRED)           ⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀        $(END)"
	@echo "$(IRED)        ⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀     $(END)"
	@echo "$(IRED)        ⣼⣿⠋       ⢀⣀⣀⠈⢻⣿⣿⡄    $(END)"
	@echo "$(IRED)       ⣸⣿⡏   ⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄   $(END)"
	@echo "$(IRED)       ⣿⣿⠁  ⢰⣿⣿⣯⠁       ⠈⠙⢿⣷⡄ $(END)"
	@echo "$(IRED)  ⣀⣤⣴⣶⣶⣿⡟   ⢸⣿⣿⣿⣆          ⣿⣷ $(END)"
	@echo "$(IRED) ⢰⣿⡟⠋⠉⣹⣿⡇   ⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿ $(END)"
	@echo "$(IRED) ⢸⣿⡇  ⣿⣿⡇    ⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃ $(END)"
	@echo "$(IRED) ⣸⣿⡇  ⣿⣿⡇     ⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇  $(END)"
	@echo "$(IRED) ⠸⣿⣧⡀ ⣿⣿⡇                ⣿⣿⠃  $(END)"
	@echo "$(IRED)  ⠛⢿⣿⣿⣿⣿⣇     ⣰⣿⣿⣷⣶⣶⣶⣶⠶ ⢠⣿⣿   $(END)"
	@echo "$(IRED)       ⣿⣿     ⣿⣿⡇ ⣽⣿⡏⠁  ⢸⣿⡇   $(END)"
	@echo "$(IRED)       ⣿⣿     ⣿⣿⡇ ⢹⣿⡆   ⣸⣿⠇   $(END)"
	@echo "$(IRED)       ⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁ ⠈⠻⣿⣿⣿⣿⡿⠏    $(END)"
	@echo "$(IRED)       ⠈⠛⠻⠿⠿⠿⠿⠋⠁              $(END)"
	@echo "$(WHITE)         ░█▀▀░█░█░█▀▀$(END)"
	@echo "$(WHITE)         ░▀▀█░█░█░▀▀█$(END)"
	@echo "$(WHITE)         ░▀▀▀░▀▀▀░▀▀▀$(END)"

.PHONY:	all clean fclean re sus
