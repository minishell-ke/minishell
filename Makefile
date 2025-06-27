NAME = minishell

# Directory
INC = -I ./include/
OBJ_DIR = obj/
LIBFT = ./libft/libft.a

# Complier
CC = cc
CFLAG = -Wall -Werror -Wextra
RM = rm -rf

SRCBASE = main env_util token token_util token_special \
		 token_word token_word_util parser parser_util syntax_checker \
		 env_util2 ft_cd ft_echo ft_env ft_exit ft_export \
		 ft_pwd ft_unset cmd_exe signal exec_utils export_utils 

SRC = $(addsuffix .c, $(addprefix srcs/, $(SRCBASE)))

OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)%.o)

start:
	@make all

# Ensure directories exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# build libft libraries
$(LIBFT):
	@make -C ./libft

# Build executable
all: $(NAME)
	@echo "\033[32m[Program is ready for use]\033[0m"

# Rule to compile object files
$(OBJ_DIR)%.o: srcs/%.c
	@$(CC) $(CFLAG) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAG) $(INC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: start all clean fclean re
