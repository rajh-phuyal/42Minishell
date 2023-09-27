NAME  = minishell

CC    = @cc

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize-address-use-after-scope

SRC = src/core/main.c \
	src/core/inputs.c \
	src/parsing/scanner.c \
	src/helpers/debug.c

OBJ   = $(patsubst src/%.c, obj/%.o, $(SRC))

# COLORS
CBOLD   = \033[0;1m
RED     = \033[0;41m
GREEN   = \033[0;42m
BLUE   = \033[0;44m
YELLOW  = \033[0;43m
RESET   = \033[0m

all: obj $(NAME)

$(NAME): $(OBJ)
	@echo "$(CBOLD)$(YELLOW)    Compiling $(NAME)   $(RESET)"
	$(CC) $(FLAGS) -lreadline -o $@ $^
	@echo "$(CBOLD)$(GREEN)      $(NAME) ready!    $(RESET)"

obj:
	@mkdir -p obj

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ) obj
	@echo "$(CBOLD)$(BLUE)      Objects removed!    $(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(CBOLD)$(BLUE)      Binaries removed!   $(RESET)\n"

re: fclean all

.PHONY: all
