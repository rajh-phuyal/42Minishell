NAME	=	pipes
CC		=	@cc
FLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address
LFT		=	libft/libft.a
INC		=	-I./libft
LIB		=	-L./libft -lft
OBJ		=	$(patsubst src/%.c, obj/%.o, $(SRC))
SRC		:=	$(wildcard src/*.c) \

# COLORS
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RESET   = \033[0m

all: $(LFT) obj $(NAME)

$(NAME): $(OBJ)
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling $(NAME)..."
	$(CC) $(FLAGS) -o $@ $^ $(LIB)
	@echo "[" "$(GREEN)OK$(RESET)" "] | $(NAME) ready!"

$(LFT):
	@echo "[" "$(YELLOW)..$(RESET)" "] | Compiling libft..."
	@make -sC libft
	@echo "[" "$(GREEN)OK$(RESET)" "] | Libft ready!"

obj:
	@mkdir -p obj
obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing object files...$(RESET)"
	@make -sC libft clean
	@rm -rf $(OBJ) obj
	@echo "[" "$(GREEN)OK$(RESET)" "] | Object files removed."

fclean: clean
	@echo "[" "$(YELLOW)..$(RESET)" "] | Removing binary files...$(RESET)"
	@make -sC libft fclean
	@rm -rf $(NAME)
	@echo "[" "$(GREEN)OK$(RESET)" "] | Binary file removed."

re: fclean all
	@make -s

.PHONY: all