NAME	=	minishell

SRCS	=	srcs/gnl/get_next_line_utils.c srcs/gnl/get_next_line.c main.c \
			srcs/pipex/child.c srcs/pipex/free.c srcs/pipex/pipex.c \
			srcs/parser/parser.c srcs/parser/ft_split_charset.c srcs/parser/ft_split_utils.c srcs/parser/parser_utils.c \
			srcs/lexer/lexer.c srcs/execution/redirections.c srcs/execution/execution.c \
			srcs/execution/execution_utils.c srcs/envp.c \
			srcs/builtins/builtins_utils.c \
	 		srcs/builtins/env.c srcs/builtins/cd.c \
			srcs/builtins/export.c \
			srcs/builtins/unset.c srcs/builtins/pwd.c \
			srcs/free.c srcs/builtins/echo.c srcs/builtins/exit.c \
			srcs/lexer/verify_quote.c srcs/parser/remove_quote.c \
			srcs/parser/line_checker.c srcs/error.c srcs/welcome.c \
			srcs/parser/parse_env.c srcs/builtins/echo_utils.c \
			srcs/builtins/export_utils.c srcs/execution/execution_2.c \
			srcs/execution/executions_utils_plus.c


OBJS	=	$(SRCS:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror -Iincludes/

LIB	=	-L. -lft

LINKING_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
COMPILE_FLAGS = -I${HOME}/.brew/opt/readline/include

RM	=	rm -f

.c.o:
		@$(CC) $(CFLAGS) $(COMPILE_FLAGS) -c $< -o ${<:.c=.o} -g

all	:
		@$(MAKE) -C ./libft
		@mv ./libft/libft.a .
		@make $(NAME)

$(NAME)	:	$(OBJS)
			@$(CC) $(LINKING_FLAGS) -o $(NAME) $(OBJS) $(LIB) -g

clean	:
		@$(MAKE) clean -C ./libft
		@$(RM) $(OBJS)

fclean	:	clean
		@$(MAKE) fclean -C ./libft
		@$(RM) $(NAME) libft.a

re	:	fclean all

.PHONY:	all clean fclean re
