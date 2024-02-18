NAME  = minishell

CC    = @cc

FLAGS =# -Wall -Wextra -Werror -g #-fsanitize=address 
INC = -I./includes

LFT   = libft/libft.a

SRC = src/core/main.c \
	src/core/inputs.c \
	src/core/signals.c \
	src/data/environment.c \
	src/data/initialization.c \
	src/builtins/export.c \
	src/builtins/env.c \
	src/builtins/pwd.c \
	src/builtins/cd.c \
	src/builtins/echo.c \
	src/builtins/exit.c \
	src/builtins/unset.c \
	src/helpers/debug.c \
	src/helpers/utils.c \
	src/helpers/envsort.c \
	src/lexing/lexer.c \
	src/lexing/strextract.c \
	src/lexing/strexpand.c \
	src/lexing/tokenizer.c \
	src/parsing/farmer.c \
	src/parsing/redir.c \
	src/parsing/word.c \
	src/parsing/heredoc.c \
	src/parsing/get_exec_path.c \
	src/executor/config_io.c \
	src/executor/close_pipes.c \
	src/executor/config_io_builtin.c \
	src/executor/executor.c \
	src/executor/system_cmd.c \
	src/executor/builtin_cmd.c \
	src/exceptions/errors.c \
	src/terminator/reset.c \
	src/terminator/liberation.c


OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

# COLORS
CBOLD   = \033[0;1m
RED     = \033[0;41m
GREEN   = \033[0;42m
BLUE    = \033[0;44m
YELLOW  = \033[0;43m
RESET   = \033[0m

all: $(LFT) obj $(NAME)

$(NAME): $(OBJ)
	@echo "$(CBOLD)$(YELLOW)    Compiling $(NAME)   $(RESET)"
	$(CC) $(FLAGS) $(INC) -o $@ $^ $(LFT) -lreadline
	@echo "$(CBOLD)$(GREEN)      $(NAME) ready!    $(RESET)"


$(LFT):
	@echo "$(CBOLD)$(YELLOW)     Compiling Libft      $(RESET)"
	@make -sC ./libft > /dev/null 2>&1
	@echo "$(CBOLD)$(GREEN)       Libft ready!       $(RESET)\n ↪"


obj:
	@mkdir -p obj

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@


clean:
	@make -sC libft clean
	@rm -rf $(OBJ) obj readline.supp
	@echo "$(CBOLD)$(BLUE)      Objects removed!    $(RESET)"

fclean: clean
	@make -sC libft fclean
	@rm -rf $(NAME)
	@echo "$(CBOLD)$(BLUE)      Binaries removed!   $(RESET)\n"

re: fclean all

run:
	@make re -s && ./minishell

lrun:
	@make -s && ./minishell

readline.supp:
	@wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp

vrun: readline.supp
	@make -s && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

mrun:
	@make -s && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME)


.PHONY: all
